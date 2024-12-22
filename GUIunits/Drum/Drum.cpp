#include "Drum.hpp"
#include <iostream>

ACD::Drum::Drum()
{
    
    

    speed=1;

    spacer=10;

    defined_spacer=ImVec2(0, 19);

    expected_drum_size=0;
    beg_pos=ImVec2(0, 0);
    end_pos=ImVec2(0, 0);
    origin_pos=ImVec2(0, 0);
    last_used_index=0;
    loaded_index=0;

    

}

void ACD::Drum::LoadResourses()
{
    LoadImage(BAR_IMG);
    LoadImage(BELL_IMG);
    LoadImage(CHERRY_IMG);
    LoadImage(DOLLAR_IMG);
    LoadImage(LEMON_IMG);
    LoadImage(ORANGE_IMG);
    LoadImage(PLUM_IMG);
    LoadImage(SEVEN_IMG);
    LoadImage(WATERMELLON_IMG);

    symb1=GetNext();
    symb2=GetNext();
    symb3=GetNext();
    
}

void ACD::Drum::Process(int drum_num)
{
    if(drum_num>=DRUMS_AMOUNT){
        return;
    }


    ImVec2 window_size=ImGui::GetWindowSize();
    origin_pos=ImGui::GetWindowPos();

    


    expected_drum_size=(window_size.x-spacer*2*DRUMS_AMOUNT)/DRUMS_AMOUNT;

    

    beg_pos=ImVec2(spacer+(expected_drum_size+spacer*2)*drum_num, spacer);
    end_pos=ImVec2(beg_pos.x+expected_drum_size, window_size.y-spacer);

    ImDrawList* canvas= ImGui::GetWindowDrawList();
    canvas->AddRectFilled(defined_spacer+origin_pos+beg_pos, origin_pos+end_pos, ImColor(255, 255, 255, 255));



    ProcessSymb(&symb1);
    //ProcessSymb(&symb1);
    //ProcessSymb(&symb1);
    //ImGui::Image((ImTextureID)(intptr_t)test_cherry.texture.texture_data, ImVec2(expected_drum_size-spacer*2, expected_drum_size-spacer*2));

    
}

ACD::Drum::~Drum()
{
}

ACD::ImgDispl ACD::Drum::GetNext()
{
    ImgDispl ret;
    ret.pos=0;

    last_used_index++;

        if(last_used_index>=loaded_index){
            last_used_index=0;
            if(IS_USE_BUNDLE_MODE)
            {
                //TODO: Add bundle mode
            }
        }
    
    ret.texture=loaded_imges[last_used_index];
    
    return ret;
}

void ACD::Drum::ProcessSymb(ImgDispl *inp)
{
    inp->pos+=speed;

    float expected_top_uv=0;
    float expected_bottom_uv=1;
    int expected_pos=0;
    int expected_size=expected_drum_size-spacer*2;

    if(inp->pos < expected_drum_size-spacer*2){
        expected_top_uv=1-float(inp->pos)/float(expected_drum_size-spacer*2);
        expected_size=inp->pos;
    }
    else if(inp->pos<end_pos.y-spacer-defined_spacer.y){
        expected_pos=inp->pos-(expected_drum_size-spacer*2);
    }
    else
    {
        expected_pos=inp->pos-(expected_drum_size-spacer*2);
        expected_bottom_uv=1-float(inp->pos-(end_pos.y-spacer-defined_spacer.y))/float(expected_drum_size-spacer*2);
        expected_size=(expected_drum_size-spacer*2)*expected_bottom_uv;

        if(expected_size<=0){
            (*inp)=GetNext();
        }
    }

    
    ImGui::SetCursorPos(ImVec2(defined_spacer.x+origin_pos.x+beg_pos.x+spacer, defined_spacer.y+origin_pos.y+beg_pos.y+expected_pos));
    ImGui::Image((ImTextureID)(intptr_t)inp->texture.texture_data, ImVec2(expected_drum_size-spacer*2, expected_size), ImVec2(0, expected_top_uv), ImVec2(1, expected_bottom_uv));

}

void ACD::Drum::LoadImage(const char* path_to_file)
{
    TextureInfo buff;
    IM_ASSERT(loaded_index<DRUM_IMAGES_AMOUNT);
    bool ret = LoadTextureFromFile(path_to_file, &buff.texture_data, &buff.texture_width, &buff.texture_height);

    IM_ASSERT(ret);
    IM_ASSERT(buff.texture_data!=0);

    loaded_imges[loaded_index]=buff;

    loaded_index++;
}
