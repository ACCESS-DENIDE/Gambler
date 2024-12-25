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


#define SEVEN_SCORE 7.0f
#define BAR_SCORE 2.0f
#define BELL_SCORE 1.5f
#define DOLLAR_SCORE 1.0f
#define WATERMELLON_SCORE 0.5f
#define ORANGE_SCORE 0.4f
#define LEMON_SCORE 0.3f
#define PLUM_SCORE 0.2f
#define CHERRY_SCORE 0.1f

#include "../../Libs/STD_img/std_image.h"

//Used for image loader
#include <stdio.h>
//GUI backend
#include <GLFW/glfw3.h>
//used for generate critical abortions
#include <assert.h>

namespace ACD
{
    /// @brief Loaded texture data container
    struct TextureInfo
    {
        int texture_width = 0;
        int texture_height = 0;
        GLuint texture_data = 0;
        float score=0;

    };



    TextureInfo* GetArrBegin();

    void LoadDrumImages();

    void LoadImage(const char* path, float symb_score);

    bool LoadTextureFromMemory(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height);
    bool LoadTextureFromFile(const char* file_name, GLuint* out_texture, int* out_width, int* out_height);

}


#endif