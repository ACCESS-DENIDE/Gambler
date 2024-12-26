#include "GUI.hpp"

/// @brief Standart constructor for Main GUI processor
ACD::GUI::GUI()
{
    Init(1280, 920, "Default Name");
}

/// @brief Specified constructor for main GUI processor
/// @param w Initial window width
/// @param h Initial window height
/// @param w_name Window display name
ACD::GUI::GUI(int w, int h, const char *w_name)
{
    Init(w, h, w_name);   
}

/// @brief Process full GUI initiation (OpenGl/LFW init, main window creation)
/// @param w width of main windo
/// @param h height of main window
/// @param name name of main window
void ACD::GUI::Init(int w, int h, const char *name)
{
    //Seting Up Main error callback
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        return;
    }
    
    //Creating Main window
    window = glfwCreateWindow(w, h, name, nullptr, nullptr);
    if (window == nullptr)
    {
        return;
    }


    //Generating main GUI context
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    //Seting up ImGui settings
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    //Switching to dark theme
    ImGui::StyleColorsDark();

    //Initiating open gl and glfw
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();


    //Load main window defaults
    show_demo_window=DEFAULT_SHOW_DEMO;
    clear_color=DEFAULT_BCGND_COLOR;

    //Seting up startup state (Idle)
    cur_state=&internal_idle;

    //Begin setting variables to default
    is_show_results=false;

    chips_amount=START_CHIP_AMOUNT;
    last_bet=0;
    last_win=0;
    cur_bet=10;
    personal_best=0;
    is_buffering_input=false;

    //Providing bet pointer to Result state
    internal_result.SetCalcBet(&cur_bet);
    

    //Loading S=memorized personal best
    LoadPB();

    //If no personal best found, or PB less then starting chp override file
    if(personal_best<chips_amount){
        personal_best=chips_amount;
        StorePB();
    }
}


/// @brief Transfers control to main GUI processor 
/// @return Error code
int ACD::GUI::Launch()
{
    //Extracting Main IO
    ImGuiIO& io=ImGui::GetIO(); (void)io;

    //Loading Textures for drums in VRAM
    LoadDrumImages();

    //Connect info window to texture storage
    q_info.LoadImages(GetArrBegin());

    //Extract tooltip's float pointer
    float* q_tip_ref=q_info.GetQTipPointer();


    //Connecting each drum to texture storage and tooltip
    for(int i=0; i<DRUMS_AMOUNT; i++){
        drum_list[i].SetLinkedTip(q_tip_ref);
        drum_list[i].ConnectResourses(GetArrBegin());
    }

    //Starting loop until window main close (or error)
    while (!glfwWindowShouldClose(window))
    {   
        //Extracting input events
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }
        
        //Process state machine frame
        int state_process_ret=cur_state->Frame(&drum_list[0]);

        //Reacting to state machine frame
        switch (cur_state->GetStateId())
        {
            case Idle:
            //Nothing
                break;
            case SpeedUp:
            //If All drums axelerated, switch to working mode
                if(state_process_ret==1){
                    TryStateSwitch(2);
                    auto_stop_timer=AUTOSTOP_SEC;
                }
                break;
            case Work:
            //subtruct frame time from timer, until zero. If zero switch to slow down
                auto_stop_timer-=1.0f/float(io.Framerate);
                if(auto_stop_timer<=0 || is_buffering_input){
                    TryStateSwitch(3);
                    is_buffering_input=false;
                }
                
                break;
            case SlowDown:
            //If all drums stoped, switch to results
                if(state_process_ret==1){
                    TryStateSwitch(4);
                    is_show_results=true;
                }
                break;
            case Result:

            //Display results, if subwindow closed, switch ti idle
                result_val=state_process_ret;

                if(!is_show_results){
                    last_win=result_val;
                    last_bet=cur_bet;
                    chips_amount+=result_val;
                    //If player's chips+award more than PB, override file
                    if(chips_amount>personal_best){
                        personal_best=chips_amount;
                        StorePB();
                    }
                    TryStateSwitch(0);
                }
                break;
            
            default:
                break;
        }

        //Process frame generation
        CreateFrame(io);
        
        //Show demo window, if requested
        if (show_demo_window){
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        //Render Generated frame
        Render();
    }


    //Clear all nitiated GLibs
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

/// @brief Handles frame creation routine
/// @param io main window IO system
/// @return Error code
int ACD::GUI::CreateFrame(ImGuiIO io)
{
    //Start new frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    
    
    //Setup docking in main window (for layout)
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode );
    
    //Generate subwindow with drums
    ImGui::Begin("Drums", NULL, ImGuiWindowFlags_NoScrollbar);
        for(int i=0; i<DRUMS_AMOUNT; i++){
            //Generate frame in each drum
            drum_list[i].Process(i);
        }

    ImGui::End();
    
    //Generate info subwindow
    ImGui::Begin("Info", NULL, ImGuiWindowFlags_NoScrollbar);    
        //Generate frame in quick info
        q_info.Process();
    ImGui::End();
    
    //Generate player's bank subwindow
    ImGui::Begin("Bank", NULL);
        //Display all player's stats
        ImGui::Text("Chips amount: %d", chips_amount);
        ImGui::Text("Personal best: %d", personal_best);
        ImGui::Text("Last Bet: %d", last_bet);
        ImGui::Text("Last Win: %d", last_win);
        ImGui::Text("Current Bet: %d", cur_bet);
        //Buffer player's bet
        int temp_bet=cur_bet;
        ImGui::SliderInt("BET", &temp_bet, MIN_BET, MAX_BET);

        //If in idle state, load bet from buffer, drop otherwise
        if(cur_state->GetStateId()==Idle){
            cur_bet=temp_bet;
        }
    
    ImGui::End();

    //button callbacks variables
    bool start_gamble_btn=false;
    bool stop_gamble_btn=false;
    
    //Start control panel subwindow
    ImGui::Begin("Control Panel", NULL);
        //Generating buttons 
        start_gamble_btn=ImGui::Button("START");
        stop_gamble_btn=ImGui::Button("STOP");
        //Displaying current state info
        ImGui::Text("Current state: ");
        ImGui::Text(cur_state->GetDisplayState());
        //If in working state, show timer
        if(cur_state->GetStateId()==Work){
            ImGui::Text("Auto stop in: %.1f", auto_stop_timer);
        }

        //Check, if player can play (enough money to bet and game in idle state)
        if(start_gamble_btn){
            if(chips_amount>=cur_bet){
                if(TryStateSwitch(1)){
                    chips_amount-=cur_bet;
                }
                
            }

        }
        //Check, if player can stop drums (if in speed up state, input will be buffered, and auto applied after all drums achive full speed)
        if(stop_gamble_btn){
            if(!TryStateSwitch(3) && cur_state->GetStateId()==SpeedUp){
                is_buffering_input=true;
            }

        }
    ImGui::End();

    //Generate result subwindow, if required
    if(is_show_results){
        ImGui::Begin("RESULTS", &is_show_results, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::Text("You win %d chips.", result_val);
            ImGui::Text("Total multiplyer: x%.1f", float(result_val)/float(cur_bet));          
        ImGui::End();
    }
    

    return 0;
}

/// @brief Handle frame rendering routine
/// @return Error code
int ACD::GUI::Render()
{
    //Default ImGui Render Process
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    glfwMakeContextCurrent(window);
    glfwSwapBuffers(window);
    return 0;

}

/// @brief Trying to switch state machine
/// @param new_state identifier of the new state
/// @return True if switch succeed, false elsewhere
bool ACD::GUI::TryStateSwitch(int new_state)
{
    //Check, is next state valid
    if(cur_state->IsValidStateSwitch(new_state)){
        //If valid, process switch betwen states 
        cur_state->OutSwitch(&drum_list[0]);

        switch (new_state)
        {
            case 0:
                cur_state=&internal_idle;
                break;
            case 1:
                cur_state=&internal_speedup;
                break;
            case 2:
                cur_state=&internal_working;
                break;
            case 3:
                cur_state=&internal_slow;
                break;
            case 4:
                cur_state=&internal_result;
                break;
           
            default:
                IM_ASSERT(false);
                break;
        }

        cur_state->OnSwitch(&drum_list[0]);
        return true;
    }
    //If not, return false
    return false;
}

/// @brief Load Personal Best from file
void ACD::GUI::LoadPB()
{

    //Open file with PB
    std::ifstream fin;
    fin.open("personal_best");
    //If file does not exist, skip this step
    if(fin.good()){
        fin>>personal_best;
    }
    fin.close();
    return;
}

/// @brief Stores Personal best to file
void ACD::GUI::StorePB()
{
    //Open file with PB, and override it
    std::ofstream fout;
    fout.open("personal_best");
    fout<<personal_best;
    fout.close();
    return;
}



/// @brief Default GUI processor deconstructor
ACD::GUI::~GUI()
{
}

/// @brief Print error to error stream, then assert
/// @param error Error code
/// @param description Text error description
void ACD::glfw_error_callback(int error, const char *description)
{
    //Throws error
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

