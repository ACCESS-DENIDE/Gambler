#ifndef DRUMM_CLASS
#define DRUMM_CLASS

//Is ude bundle mode to next symbol (check readme)
#define IS_USE_BUNDLE_MODE true

//Amount of drums in set
#define DRUMS_AMOUNT 5
//Space betwen drums |D||D||D|
#define DRUM_SPACER 10

//Max axelerated spin speed
#define MAX_WORKING_SPEED 5
//Minimal axelerated spin speed
#define MIN_WORKING_SPEED 2

//Max axeleration
#define MAX_AXEL_SPEED 1
//Minimal axeleration
#define MIN_AXEL_SPEED 0.5

//Max speed dump on slowDown
#define MAX_DUMP_SPEED 2
//Min speed dump on slowDown
#define MIN_DUMP_SPEED 1

#define SPRING_SPEED 0.1



#include "../../Classes/GUIunit/GUIunit.hpp"
#include "../../Libs/MiniLib/MiniLib.hpp"
#include "../../Libs/ImageLoader/ImageLoader.hpp"

//Used for Abs() function
#include <math.h>

namespace ACD{

    /// @brief Internal struct for storing symbol position and texture
    struct ImgDispl
    {
        TextureInfo texture;

        float pos;
    };

    /// @brief Class for processing all drumm logic
    class Drum:GUIunit{
        private:
            /// @brief spacer between drums (used for internal calculation)
            int spacer;
            /// @brief expected drum width (used for internal calculation)
            int expected_drum_size;
            /// @brief top left corner of white background
            ImVec2 beg_pos;
            /// @brief bottom right corner of white background
            ImVec2 end_pos;
            /// @brief subwindow global position
            ImVec2 origin_pos;

            /// @brief Array of loaded symbols (used for processing new symbols)
            TextureInfo loaded_imges[DRUM_IMAGES_AMOUNT];
            /// @brief memorised last used symbol in loaded array
            char last_used_index;
            /// @brief top border for loaded_images array (security reasons)
            char loaded_index;
            
            /// @brief current drum spinning speed
            float speed;
            /// @brief axeleration/slowdown of drum
            double speed_delta;
            /// @brief max drum speed in this round
            float max_speed;

            /// @brief Symbol 1 on drum
            ImgDispl symb1;
            /// @brief Symbol 2 on drum
            ImgDispl symb2;
            /// @brief Symbol 3 on drum
            ImgDispl symb3;

            /// @brief Check, if need to change speed in this frame
            bool is_speed_change;
            /// @brief check, is in break(full stop) mode
            bool is_break_mode;
            /// @brief Estimate Time to Arrival (time before full stop)
            double eta;

            /// @brief Link to tooltip's float (for showing symbol score)
            float* linked_tip;

            /// @brief Time passed from last frame msec
            float frametime;


            ImgDispl GetNext();
            void ProcessSymb(ImgDispl* inp);

            void Align(int from, float pos);


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