#pragma once

#include "../GUIunit/GUIunit.hpp"

#include "../../GUIunits/Drum/Drum.hpp"

#define DEFAULT_SHOW_DEMO false
#define DEFAULT_BCGND_COLOR ImVec4(0.45f, 0.55f, 0.60f, 1.00f)

namespace ACD{

    class GUI{
        private:
            GLFWwindow *window;
            bool show_demo_window;
            ImVec4 clear_color;
            ACD::Drum test_drum;

            int CreateFrame(ImGuiIO io);
            int Render();

        public:
            GUI();
            GUI(int w, int h, const char *w_name);
            int Launch();
            ~GUI();


    };

    static void glfw_error_callback(int error, const char* description);
}