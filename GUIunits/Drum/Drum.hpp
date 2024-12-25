#ifndef DRUMM_CLASS
#define DRUMM_CLASS


#define IS_USE_BUNDLE_MODE true

#define DRUMS_AMOUNT 5
#define DRUM_SPACER 10

#define MAX_WORKING_SPEED 5
#define MIN_WORKING_SPEED 2

#define MAX_AXEL_SPEED 1
#define MIN_AXEL_SPEED 0.5

#define MAX_DUMP_SPEED 2
#define MIN_DUMP_SPEED 1

#define SPRING_SPEED 0.1



#include "../../Classes/GUIunit/GUIunit.hpp"
#include "../../Libs/MiniLib/MiniLib.hpp"
#include "../../Libs/ImageLoader/ImageLoader.hpp"

#include <math.h>

namespace ACD{
    struct ImgDispl
    {
        TextureInfo texture;

        float pos;
    };

    class Drum:GUIunit{
        private:

            int spacer;
            int expected_drum_size;
            ImVec2 beg_pos;
            ImVec2 end_pos;
            ImVec2 origin_pos;

            TextureInfo loaded_imges[DRUM_IMAGES_AMOUNT];
            char last_used_index;
            char loaded_index;

            ImVec2 defined_spacer;
            
            float speed;
            double speed_delta;
            float max_speed;

            ImgDispl symb1;
            ImgDispl symb2;
            ImgDispl symb3;

            ImgDispl test_cherry;

            bool is_speed_change;
            bool is_break_mode;
            double eta;

            float* linked_tip;

            ImgDispl GetNext();
            void ProcessSymb(ImgDispl* inp);

            void Align(int from, float pos);

            float frametime;

        public:
            Drum();
            void SetLinkedTip(float * inp);
            void Start();
            void Slow();
            bool GetState(float * ret_score=nullptr, GLuint* ref_to_texture=nullptr);
            void ConnectResourses(TextureInfo* arr_ref);
            void Process(int drum_num);
            ~Drum();
    };

}

#endif