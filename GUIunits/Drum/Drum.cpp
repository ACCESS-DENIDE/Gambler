#include "Drum.hpp"

/// @brief Default constructor for slot machine drum
ACD::Drum::Drum()
{
    //Loading default values
    speed=0;

    spacer=DRUM_SPACER;


    expected_drum_size=0;
    beg_pos=ImVec2(0, 0);
    end_pos=ImVec2(0, 0);
    origin_pos=ImVec2(0, 0);
    last_used_index=0;
    loaded_index=0;

    speed_delta=-0.3;
    max_speed=0;
    is_speed_change=false;
    is_break_mode=false;
    frametime=0;
    eta=0;

    linked_tip=nullptr;

    

}


/// @brief Setup link to tooltip instrument (to show symbol scores)
/// @param inp pointer to tooltip's float
void ACD::Drum::SetLinkedTip(float *inp)
{
    linked_tip=inp;
}

/// @brief Starts axeleration of drum
void ACD::Drum::Start()
{
    //Setting flags to speed up mode
    is_break_mode=false;
    is_speed_change=true;

    //Generating max speed and axeliration for this round
    speed=0;
    max_speed=RandomFloat(float(MIN_WORKING_SPEED), float(MAX_WORKING_SPEED));
    speed_delta=RandomFloat(float(MIN_AXEL_SPEED), float(MAX_AXEL_SPEED));
    
}

/// @brief Starts drum slowdown
void ACD::Drum::Slow()
{
    //Setting flags to slow down mode
    is_break_mode=false;
    is_speed_change=true;

    //Generating antiaxeliration for this round
    speed_delta=-RandomFloat(float(MIN_AXEL_SPEED), float(MAX_AXEL_SPEED));
    
}


/// @brief Check, if drums stop speed change (speedUp/SlowDown), and returns current symbol
/// @param ret_score reference to store current symbol score
/// @param ref_to_texture reference to store current symbol texture id
/// @return true if all speed change processes ended, false otherwise
bool ACD::Drum::GetState(float * ret_score, GLuint* ref_to_texture)
{
    //Check, if speed is changing now
    if(is_speed_change){
        //If it changes, return false with error values
        if(ret_score!=nullptr){
            (*ret_score)=0;
        }
        if(ref_to_texture!=nullptr){
            (*ref_to_texture)=0;
        }
        
        return false;
    }

    //Otherwise search for nearest value to 0.5(middle of drum)
    float found_score=0;
    GLint found_ref=0;

    double aproach1=abs(symb1.pos-0.5);
    double aproach2=abs(symb2.pos-0.5);
    double aproach3=abs(symb3.pos-0.5);

    int sellected_aproach=0;

    Min(3, &sellected_aproach, aproach1, aproach2, aproach3);

    //Storing nearest value to buffers
    switch(sellected_aproach)
    {
        case 0:
            found_score=symb1.texture.score;
            found_ref=symb1.texture.texture_data;
            break;
        case 1:
            found_score=symb2.texture.score;
            found_ref=symb2.texture.texture_data;
            break;
        case 2:
            found_score=symb3.texture.score;
            found_ref=symb3.texture.texture_data;
            break;
        default:
            //HOW??
            found_score=0;
            break;
    }

    //Return all requested data from buffers
    if(ret_score!=nullptr){
        (*ret_score)=found_score;
    }
    if(ref_to_texture!=nullptr){
        (*ref_to_texture)=found_ref;
    }
    
    return true;
    
}

/// @brief Copy references to textures of symbols from ImageLoader
/// @param arr_ref pointer to LoadedTextures array
void ACD::Drum::ConnectResourses(TextureInfo* arr_ref)
{
    //Copy reference to all textures to local memory
    
    for (loaded_index=0; loaded_index<DRUM_IMAGES_AMOUNT; loaded_index++)
    {
        loaded_imges[loaded_index]=arr_ref[loaded_index];

    }

    //If in bundle mode, shuffle array before usage
    if(IS_USE_BUNDLE_MODE){
        Shuffle(&loaded_imges[0], 9);
    }
    
    //Reading first symbols
    symb1=GetNext();
    symb2=GetNext();
    symb3=GetNext();

    //Allign symbols to initial position
    const float initial_pos=0.16666675;
    Align(0, initial_pos);
    
}


/// @brief Generate new frame for drum
/// @param drum_num position of drum in set (from 0)
void ACD::Drum::Process(int drum_num)
{
    //Throw return, if wrong drum number
    if(drum_num>=DRUMS_AMOUNT){
        return;
    }

    //Calculating frametime
    frametime=1.0f/ImGui::GetIO().Framerate;

    //Calculating default spacers
    ImVec2 window_size=ImGui::GetWindowSize();
    origin_pos=ImGui::GetWindowPos();


    if(is_speed_change){
            //If in speed change mode
            //Calculate new speed, and check, if overspiled maximum/minimum

            speed+=speed_delta*frametime;
            if(speed>=max_speed){
                //if max speed have been reached, switch to working mode
                speed=max_speed;
                is_speed_change=false;
            }
            //Check, if in slowdown mode, to switch to break mode
            if(speed_delta<0 & !is_break_mode){
                if((speed+(speed_delta*frametime))<=SPRING_SPEED){
                    //Find nearest symb to break (0.5)
                    double aproach1=abs(symb1.pos-0.5);
                    double aproach2=abs(symb2.pos-0.5);
                    double aproach3=abs(symb3.pos-0.5);

                    double best_aproach=0;
                    int sellected_aproach=0;

                    Min(3, &sellected_aproach, aproach1, aproach2, aproach3);
                    //Storing exact position of selected symbol
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

                    //Recalculating antiaxeleration (like catch on spring)
                    eta=speed/abs(speed_delta);

                    speed_delta=(2*((0.5-best_aproach)-speed*eta))/pow(eta, 2);
                    
                    //Switch to break mode
                    is_break_mode=true;


                }
            }
        
    }

    //if in break mode, process countdown to full stop
    if(is_break_mode){
        eta-=frametime;

        if(eta<=0)
        {
            //Processing full stop, if countdown reached zero
            speed=0;
            speed_delta=0;
            is_break_mode=false;
            is_speed_change=false;

            int smallest=0;
            Min(3, &smallest, double(symb1.pos), double(symb2.pos), double(symb3.pos));

            //Final alignment to be exactly as all other drums
            Align(smallest, 0.16666675);
        }
    }

    //Calculating background width
    expected_drum_size=(window_size.x-spacer*2*DRUMS_AMOUNT)/DRUMS_AMOUNT;

    
    //Calculating background points
    beg_pos=ImVec2(spacer+(expected_drum_size+spacer*2)*drum_num, spacer);
    end_pos=ImVec2(beg_pos.x+expected_drum_size, window_size.y-spacer);

    //Displaying background
    ImDrawList* canvas= ImGui::GetWindowDrawList();
    canvas->AddRectFilled(WINDOW_TOP_SPACER+origin_pos+beg_pos, origin_pos+end_pos, ImColor(255, 255, 255, 255));


    //Processing each symbol
    ProcessSymb(&symb1);
    ProcessSymb(&symb2);
    ProcessSymb(&symb3);
    
}


/// @brief default drum deconstructor
ACD::Drum::~Drum()
{

}


/// @brief Internal function to get next symbol
/// @return New symbol texture
ACD::ImgDispl ACD::Drum::GetNext()
{
    //Set position of new symbol to zero
    ImgDispl ret;
    ret.pos=0;

    //Increase last index
    last_used_index++;

        //If last index overflowed, drop it to zero
        if(last_used_index>=loaded_index){
            last_used_index=0;
            if(IS_USE_BUNDLE_MODE)
            {
                //If in bundle mode, shuffle array
                Shuffle(&loaded_imges[0], DRUM_IMAGES_AMOUNT);
            }
        }
    
    ret.texture=loaded_imges[last_used_index];
    
    return ret;
}


/// @brief Move symbols through drum
/// @param inp pointer to moving symbol
void ACD::Drum::ProcessSymb(ImgDispl *inp)
{
    //Calculating frame constats (can be changed between frames because of layout)
    const int texture_side=expected_drum_size-spacer*2;
    const int visible_path=end_pos.y-beg_pos.y;
    const ImVec2 ext_spacers=WINDOW_TOP_SPACER+origin_pos+beg_pos;
    const int frame_path=visible_path+texture_side-WINDOW_TOP_SPACER.y;

    //Applying speedchange (frametime used for smoothing instable FPS)
    inp->pos+=speed*frametime;

    //Setting up vars to default
    float expected_top_uv=0;
    float expected_bottom_uv=1;
    int expected_pos=0;
    int expected_size=texture_side;

    //Checking, in which state texture is (Apear, Move, Disaper)
    if(inp->pos<float(texture_side)/float(frame_path))
    {
        //If Apearing, Cut top part of texture
        expected_top_uv=1-(inp->pos/(float(texture_side)/float(frame_path)));
        expected_size=texture_side*(inp->pos/(float(texture_side)/float(frame_path)));
    }
    else if(inp->pos<float(visible_path-WINDOW_TOP_SPACER.y)/float(frame_path))
    {
        //If moving, change position of teture
        expected_pos=(frame_path*inp->pos)-texture_side;
        if(inp->pos>1){
            expected_pos;
        }
    }
    else
    {
        //If disapearing, change position and cut bottom part of texture
        expected_pos=(frame_path*inp->pos)-texture_side;
        expected_bottom_uv=(end_pos.y-(ext_spacers.y+expected_pos))/texture_side;
        expected_size=texture_side*expected_bottom_uv;


        //If all texture disapeared, switch to next texture
        if(inp->pos+speed*frametime>=1){
            float overspill=inp->pos-1;
            (*inp)=GetNext();

            inp->pos=overspill;

        }
    }

    
    

    //Display texture in requested pos    
    ImGui::SetCursorPos(ImVec2(ext_spacers.x+spacer, ext_spacers.y+expected_pos));
    ImGui::Image((ImTextureID)(intptr_t)inp->texture.texture_data, ImVec2(texture_side, expected_size), ImVec2(0, expected_top_uv), ImVec2(1, expected_bottom_uv));
    
    //If texture hovered, show tooltip about texture score
    if(ImGui::IsItemHovered()){
        if(linked_tip!=nullptr){
            (*linked_tip)=inp->texture.score;
        }
        
    }
}


/// @brief Automaticaly allign symbols on drum
/// @param from symbol start from
/// @param pos Y position of "from" symbol
void ACD::Drum::Align(int from, float pos)
{
    //Allign textures with 1/3 of free space
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
