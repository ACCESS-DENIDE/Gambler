#ifndef GUI_UNIT_CLASS
#define GUI_UNIT_CLASS

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC


#include "../../Libs/STD_img/std_image.h"

#include "../../Libs/ImGUI/imgui/imgui.h"
#include "../../Libs/ImGUI/backend/imgui_impl_glfw.h"
#include "../../Libs/ImGUI/backend/imgui_impl_opengl2.h"
#include <stdio.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif


#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace ACD{

    class GUIunit{
        private:
            
        public:
            GUIunit();
            void Process();
            ~GUIunit();


    };

    ImVec2 operator+ (const ImVec2 a, const ImVec2 b);

    bool LoadTextureFromMemory(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height);
    bool LoadTextureFromFile(const char* file_name, GLuint* out_texture, int* out_width, int* out_height);

}
#endif