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
}

int ACD::GUI::Launch()
{

    ImGuiIO& io=ImGui::GetIO(); (void)io;

    test_drum1.LoadResourses();
    test_drum2.LoadResourses();
    test_drum3.LoadResourses();
    test_drum4.LoadResourses();
    test_drum5.LoadResourses();

    while (!glfwWindowShouldClose(window))
    {   
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
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
    
    test_drum1.Process(0);
    test_drum2.Process(1);
    test_drum3.Process(2);
    test_drum4.Process(3);
    test_drum5.Process(4);

    ImGui::End();
    
    ImGui::Begin("Info", NULL);    
    ImGui::End();
    
    ImGui::Begin("Bank", NULL);    
    ImGui::End();

    bool start_gamble_btn=false;
    bool stop_gamble_btn=false;
    
    ImGui::Begin("Control Panel", NULL); 
        start_gamble_btn=ImGui::Button("START");
        stop_gamble_btn=ImGui::Button("STOP");
        ImGui::Spacing();
        //ImGui::SliderInt("Bet", &test_drum.speed, 1, 10);
        if(start_gamble_btn){

            test_drum1.Start();
            test_drum2.Start();
            test_drum3.Start();
            test_drum4.Start();
            test_drum5.Start();
            

        }
        if(stop_gamble_btn){
            test_drum1.Slow();
            test_drum2.Slow();
            test_drum3.Slow();
            test_drum4.Slow();
            test_drum5.Slow();
            
        }
    ImGui::End();

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

ACD::GUI::~GUI()
{
}

void ACD::glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

