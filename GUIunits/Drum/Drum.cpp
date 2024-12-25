#include "Drum.hpp"
#include <iostream>

ACD::Drum::Drum()
{
    
    

    speed=0;

    spacer=DRUM_SPACER;

    defined_spacer=ImVec2(0, 19);

    expected_drum_size=0;
    beg_pos=ImVec2(0, 0);
    end_pos=ImVec2(0, 0);
    origin_pos=ImVec2(0, 0);
    defined_spacer=ImVec2(0, 19);
    last_used_index=0;
    loaded_index=0;

    speed_delta=-0.3;
    max_speed=0;
    is_speed_change=false;
    is_break_mode=false;
    frametime=0;
    eta=0;

    

}

void ACD::Drum::Start()
{
    is_break_mode=false;
    is_speed_change=true;

    speed=0;
    max_speed=RandomFloat(float(MIN_WORKING_SPEED), float(MAX_WORKING_SPEED));
    speed_delta=RandomFloat(float(MIN_AXEL_SPEED), float(MAX_AXEL_SPEED));
    
}

void ACD::Drum::Slow()
{
    is_break_mode=false;
    is_speed_change=true;

    speed_delta=-RandomFloat(float(MIN_AXEL_SPEED), float(MAX_AXEL_SPEED));
    
}

bool ACD::Drum::GetState(int * ret_state)
{
    if(is_speed_change){

        if(ret_state!=nullptr){
            (*ret_state)=-1;
        }
        
        return false;
    }
    


    if(ret_state!=nullptr){
        (*ret_state)=-1;
    }
    return true;
    
}

void ACD::Drum::ConnectResourses(TextureInfo* arr_ref)
{
    const float initial_pos=0.16666675;

    for (loaded_index=0; loaded_index<DRUM_IMAGES_AMOUNT; loaded_index++)
    {
        loaded_imges[loaded_index]=arr_ref[loaded_index];

    }

    if(IS_USE_BUNDLE_MODE){
        Shuffle(&loaded_imges[0], 9);
    }
    
    symb1=GetNext();
    symb2=GetNext();
    symb3=GetNext();

    Align(0, initial_pos);
    
}

void ACD::Drum::Process(int drum_num)
{
    if(drum_num>=DRUMS_AMOUNT){
        return;
    }

    frametime=1.0f/ImGui::GetIO().Framerate;

    ImVec2 window_size=ImGui::GetWindowSize();
    origin_pos=ImGui::GetWindowPos();


    if(is_speed_change){


            speed+=speed_delta*frametime;
            if(speed>=max_speed){
                speed=max_speed;
                is_speed_change=false;
            }

            if(speed_delta<0 & !is_break_mode){
                if((speed+(speed_delta*frametime))<=SPRING_SPEED){
                    double aproach1=abs(symb1.pos-0.5);
                    double aproach2=abs(symb2.pos-0.5);
                    double aproach3=abs(symb3.pos-0.5);

                    double best_aproach=0;
                    int sellected_aproach=0;

                    Min(3, &sellected_aproach, aproach1, aproach2, aproach3);

                    switch(sellected_aproach)
                    {
                        case 0:
                            best_aproach=symb1.pos;
                            break;
                        case 1:
                            best_aproach=symb2.pos;
                            break;
                        case 2:
                            best_aproach=symb3.pos;
                            break;
                        default:
                            //HOW??
                            IM_ASSERT(false);
                            break;
                    }

                    eta=speed/abs(speed_delta);

                    speed_delta=(2*((0.5-best_aproach)-speed*eta))/pow(eta, 2);
                    
                    is_break_mode=true;


                }
            }
        
    }

    if(is_break_mode){
        eta-=frametime;

        if(eta<=0)
        {
            speed=0;
            speed_delta=0;
            is_break_mode=false;
            is_speed_change=false;

            int smallest=0;
            Min(3, &smallest, double(symb1.pos), double(symb2.pos), double(symb3.pos));

            Align(smallest, 0.16666675);
        }
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
                Shuffle(&loaded_imges[0], DRUM_IMAGES_AMOUNT);
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

    inp->pos+=speed*frametime;

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


        if(inp->pos+speed*frametime>=1){
            float overspill=inp->pos-1;
            (*inp)=GetNext();

            inp->pos=overspill;

        }
    }

    
    

    
    ImGui::SetCursorPos(ImVec2(ext_spacers.x+spacer, ext_spacers.y+expected_pos));
    ImGui::Image((ImTextureID)(intptr_t)inp->texture.texture_data, ImVec2(texture_side, expected_size), ImVec2(0, expected_top_uv), ImVec2(1, expected_bottom_uv));

}

void ACD::Drum::Align(int from, float pos)
{
    switch(from)
    {
        case 0:
            symb1.pos=pos;
            symb2.pos=pos+1.0f/3.0f;
            symb3.pos=pos+2.0f/3.0f;
            
            break;

        case 1:
            symb2.pos=pos;
            symb3.pos=pos+1.0f/3.0f;
            symb1.pos=pos+2.0f/3.0f;
            break;

        case 2:
            symb3.pos=pos;
            symb1.pos=pos+1.0f/3.0f;
            symb2.pos=pos+2.0f/3.0f;
            break;

        default:
            IM_ASSERT(false);
            break;

        
    }
}
