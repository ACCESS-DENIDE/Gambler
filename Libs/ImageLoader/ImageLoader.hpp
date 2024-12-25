#ifndef IMAGE_LOADER_LIB
#define IMAGE_LOADER_LIB

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC

#define DRUM_IMAGES_AMOUNT 9


#define BAR_IMG "../Images/Gamblers_Bar.png"
#define BELL_IMG "../Images/Gamblers_Bell.png"
#define CHERRY_IMG "../Images/Gamblers_Cherry.png"
#define DOLLAR_IMG "../Images/Gamblers_Dollar.png"
#define LEMON_IMG "../Images/Gamblers_Lemon.png"
#define ORANGE_IMG "../Images/Gamblers_Orange.png"
#define PLUM_IMG "../Images/Gamblers_Plum.png"
#define SEVEN_IMG "../Images/Gamblers_Seven.png"
#define WATERMELLON_IMG "../Images/Gamblers_Watermellon.png"

#include "../../Libs/STD_img/std_image.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <assert.h>

namespace ACD
{
    struct TextureInfo
    {
        int texture_width = 0;
        int texture_height = 0;
        GLuint texture_data = 0;

    };



    TextureInfo* GetArrBegin();

    void LoadDrumImages();

    void LoadImage(const char* path);

    bool LoadTextureFromMemory(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height);
    bool LoadTextureFromFile(const char* file_name, GLuint* out_texture, int* out_width, int* out_height);

}


#endif