#ifndef INFO_SCREEN_GUI
#define INFO_SCREEN_GUI

#define INFO_SPACER 10

#include "../../Classes/GUIunit/GUIunit.hpp"
#include "../../Libs/MiniLib/MiniLib.hpp"
#include "../../Libs/ImageLoader/ImageLoader.hpp"

namespace ACD
{
    class InfoScreen:GUIunit{
        private:
            TextureInfo* loaded_list;
            float q_tip;


        public:
            float* GetQTipPointer();
            void LoadImages(TextureInfo* inp);
            void Process();
    };
}


#endif