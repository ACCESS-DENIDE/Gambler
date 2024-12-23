#include "Drum.hpp"
#include <iostream>

ACD::Drum::Drum()
{
    
    

    speed=0.1;

    spacer=10;

    defined_spacer=ImVec2(0, 19);

    expected_drum_size=0;
    beg_pos=ImVec2(0, 0);
    end_pos=ImVec2(0, 0);
    origin_pos=ImVec2(0, 0);
    last_used_index=0;
    loaded_index=0;

    is_axeliration=false;
    is_slow_down=true;

    

}

void ACD::Drum::LoadResourses()
{
    const float initial_pos=0.5;
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
    symb1.pos=initial_pos;
    symb2=GetNext();
    symb2.pos=initial_pos+1.0f/3.0f;
    symb3=GetNext();
    symb3.pos=initial_pos+2.0f/3.0f;
    
}

void ACD::Drum::Process(int drum_num)
{
    if(drum_num>=DRUMS_AMOUNT){
        return;
    }


    ImVec2 window_size=ImGui::GetWindowSize();
    origin_pos=ImGui::GetWindowPos();

    if(is_axeliration){
        speed+=AXELERATION_SPEED/(ImGui::GetIO().Framerate);
        if(speed>=MAX_ROTATION_SPEED){
            speed=MAX_ROTATION_SPEED;
            is_axeliration=false;
        }
    }

    if(is_slow_down){

        if(speed-DUMP_SPEED/(ImGui::GetIO().Framerate)<=0){
            double aproach1=abs(symb1.pos-0.5);
            double aproach2=abs(symb2.pos-0.5);
            double aproach3=abs(symb3.pos-0.5);

            double best_aproach=Min(3, aproach1, aproach2, aproach3);

            if(best_aproach>0){
                speed=-speed;
            }
            is_slow_down=false;
            is_break_mode=true;

        }

        speed-=DUMP_SPEED/(ImGui::GetIO().Framerate);

        if(speed<=0){
            speed=0;
            is_slow_down=0;
        }
    }

    if(is_break_mode)
    {
        
    }

    expected_drum_size=(window_size.x-spacer*2*DRUMS_AMOUNT)/DRUMS_AMOUNT;

    

    beg_pos=ImVec2(spacer+(expected_drum_size+spacer*2)*drum_num, spacer);
    end_pos=ImVec2(beg_pos.x+expected_drum_size, window_size.y-spacer);

    ImDrawList* canvas= ImGui::GetWindowDrawList();
    canvas->AddRectFilled(defined_spacer+origin_pos+beg_pos, origin_pos+end_pos, ImColor(255, 255, 255, 255));



    ProcessSymb(&symb1);
    ProcessSymb(&symb2);
    ProcessSymb(&symb3);
    
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
    const int texture_side=expected_drum_size-spacer*2;
    const int visible_path=end_pos.y-beg_pos.y;
    const ImVec2 ext_spacers=defined_spacer+origin_pos+beg_pos;
    const int frame_path=visible_path+texture_side-defined_spacer.y;

    inp->pos+=speed/(ImGui::GetIO().Framerate);

    float expected_top_uv=0;
    float expected_bottom_uv=1;
    int expected_pos=0;
    int expected_size=texture_side;


    if(inp->pos<float(texture_side)/float(frame_path))
    {
        expected_top_uv=1-(inp->pos/(float(texture_side)/float(frame_path)));
        expected_size=texture_side*(inp->pos/(float(texture_side)/float(frame_path)));
    }
    else if(inp->pos<float(visible_path-defined_spacer.y)/float(frame_path))
    {
        expected_pos=(frame_path*inp->pos)-texture_side;
        if(inp->pos>1){
            expected_pos;
        }
    }
    else
    {
        expected_pos=(frame_path*inp->pos)-texture_side;
        expected_bottom_uv=(end_pos.y-(ext_spacers.y+expected_pos))/texture_side;
        expected_size=texture_side*expected_bottom_uv;


        if(inp->pos+speed/(ImGui::GetIO().Framerate)>=1){
            float overspill=inp->pos-1;
            (*inp)=GetNext();

            inp->pos=overspill;

        }
    }

    
    

    
    ImGui::SetCursorPos(ImVec2(ext_spacers.x+spacer, ext_spacers.y+expected_pos));
    ImGui::Image((ImTextureID)(intptr_t)inp->texture.texture_data, ImVec2(texture_side, expected_size), ImVec2(0, expected_top_uv), ImVec2(1, expected_bottom_uv));

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
