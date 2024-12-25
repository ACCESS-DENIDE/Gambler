#ifndef GUI_UNIT_CLASS
#define GUI_UNIT_CLASS



#include "../../Libs/ImGUI/imgui/imgui.h"
#include "../../Libs/ImGUI/backend/imgui_impl_glfw.h"
#include "../../Libs/ImGUI/backend/imgui_impl_opengl2.h"
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#define WINDOW_TOP_SPACER ImVec2(0, 19)

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace ACD{

    class GUIunit{
        private:
            
        public:
            GUIunit();
            virtual void Process();
            ~GUIunit();


    };

    ImVec2 operator+ (const ImVec2 a, const ImVec2 b);
    ImVec2 operator- (const ImVec2 a, const ImVec2 b);
    
}
#endif