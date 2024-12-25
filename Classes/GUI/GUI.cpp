#include "GUI.hpp"

ACD::GUI::GUI()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        return;
    }

    window = glfwCreateWindow(1208, 920, "Default window name", nullptr, nullptr);
    if (window == nullptr)
    {
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io=ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    show_demo_window=DEFAULT_SHOW_DEMO;
    clear_color=DEFAULT_BCGND_COLOR;

    cur_state=&internal_idle;

    is_show_results=false;

    chips_amount=START_CHIP_AMOUNT;
    last_bet=0;
    last_win=0;
    cur_bet=10;

    is_buffering_input=false;
}

ACD::GUI::GUI(int w, int h, const char *w_name)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        return;
    }
    
    window = glfwCreateWindow(w, h, w_name, nullptr, nullptr);
    if (window == nullptr)
    {
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    show_demo_window=DEFAULT_SHOW_DEMO;
    clear_color=DEFAULT_BCGND_COLOR;

    cur_state=&internal_idle;

    is_show_results=false;

    chips_amount=START_CHIP_AMOUNT;
    last_bet=0;
    last_win=0;
    cur_bet=10;


    is_buffering_input=false;
}

int ACD::GUI::Launch()
{

    ImGuiIO& io=ImGui::GetIO(); (void)io;

    LoadDrumImages();

    for(int i=0; i<DRUMS_AMOUNT; i++){
        drum_list[i].ConnectResourses(GetArrBegin());
    }

    while (!glfwWindowShouldClose(window))
    {   
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        int state_process_ret=cur_state->Frame(&drum_list[0]);

        switch (cur_state->GetStateId())
        {
            case 0:
                break;
            case 1:
                if(state_process_ret==1){
                    TryStateSwitch(2);
                    auto_stop_timer=AUTOSTOP_SEC;
                }
                break;
            case 2:
                auto_stop_timer-=1.0f/float(io.Framerate);
                if(auto_stop_timer<=0 || is_buffering_input){
                    TryStateSwitch(3);
                    is_buffering_input=false;
                }
                
                break;
            case 3:
                if(state_process_ret==1){
                    TryStateSwitch(4);
                    is_show_results=true;
                }
                break;
            case 4:
                result_val=state_process_ret;

                if(!is_show_results){
                    last_win=result_val;
                    last_bet=cur_bet;
                    chips_amount+=result_val;
                    TryStateSwitch(0);
                }
                break;
            
            default:
                break;
        }

        CreateFrame(io);
        
        if (show_demo_window){
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        Render();
    }

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

int ACD::GUI::CreateFrame(ImGuiIO io)
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    
    
    

    bool show_drums=true;
    
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoResize);
    
    ImGui::Begin("Drums", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    
    for(int i=0; i<DRUMS_AMOUNT; i++){
        drum_list[i].Process(i);
    }

    ImGui::End();
    
    ImGui::Begin("Info", NULL);    
    ImGui::End();
    
    ImGui::Begin("Bank", NULL);
    ImGui::Text("Chips amount: %d", chips_amount);
    ImGui::Text("Last Bet: %d", last_bet);
    ImGui::Text("Chips Win: %d", last_win);
    ImGui::Text("Current Bet: %d", cur_bet);
    int temp_bet=cur_bet;
    ImGui::SliderInt("BET", &temp_bet, MIN_BET, MAX_BET);

    if(cur_state->GetStateId()==0){
        cur_bet=temp_bet;
    }
    
    ImGui::End();

    bool start_gamble_btn=false;
    bool stop_gamble_btn=false;
    
    ImGui::Begin("Control Panel", NULL); 
        start_gamble_btn=ImGui::Button("START");
        stop_gamble_btn=ImGui::Button("STOP");
        ImGui::Text("Current state: ");
        ImGui::Text(cur_state->GetDisplayState(nullptr));
        if(cur_state->GetStateId()==2){
            ImGui::Text("Auto stop in: %.1f", auto_stop_timer);
        }

        if(start_gamble_btn){
            if(chips_amount>=cur_bet){
                if(TryStateSwitch(1)){
                    chips_amount-=cur_bet;
                }
                
            }

        }
        if(stop_gamble_btn){
            //TODO: Заменить все ID на Enum 
            if(!TryStateSwitch(3) && cur_state->GetStateId()==1){
                is_buffering_input=true;
            }

        }
    ImGui::End();

    if(is_show_results){
        ImGui::Begin("RESULTS", &is_show_results, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::Text("You win %d chips.", result_val);
        ImGui::End();
    }
    

    return 0;
}

int ACD::GUI::Render()
{
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

bool ACD::GUI::TryStateSwitch(int new_state)
{
    if(cur_state->IsValidStateSwitch(new_state)){
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
    return false;
}

ACD::GUI::~GUI()
{
}

void ACD::glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

