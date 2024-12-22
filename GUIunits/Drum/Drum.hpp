#pragma once


#define IS_USE_BUNDLE_MODE false

#define DRUMS_AMOUNT 5
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


#include "../../Classes/GUIunit/GUIunit.hpp"

namespace ACD{
    struct TextureInfo
    {
        int texture_width = 0;
        int texture_height = 0;
        GLuint texture_data = 0;

    };

    struct ImgDispl
    {
        TextureInfo texture;

        float pos;
    };

    class Drum:GUIunit{
        private:

            int spacer=10;
            int expected_drum_size;
            ImVec2 beg_pos;
            ImVec2 end_pos;
            ImVec2 origin_pos;

            TextureInfo loaded_imges[DRUM_IMAGES_AMOUNT];
            char last_used_index;
            char loaded_index;

            ImVec2 defined_spacer=ImVec2(0, 19);
            

            ImgDispl symb1;
            ImgDispl symb2;
            ImgDispl symb3;

            ImgDispl test_cherry;

            ImgDispl GetNext();
            void ProcessSymb(ImgDispl* inp);

            void LoadImage(const char* path_to_file);

        public:
            Drum();
            float speed;
            void LoadResourses();
            void Process(int drum_num);
            ~Drum();
    };

}