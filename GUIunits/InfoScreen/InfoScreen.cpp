#include "InfoScreen.hpp"

/// @brief Return pointer to tooltip's float
/// @return pointer to float
float *ACD::InfoScreen::GetQTipPointer()
{
    return &q_tip;
}


/// @brief Copy references to loaded images
/// @param inp pointer to LoadedTextures array
void ACD::InfoScreen::LoadImages(TextureInfo *inp)
{
    loaded_list=inp;
}


/// @brief Generate new frame
void ACD::InfoScreen::Process()
{
    //calculating frame constants
    ImVec2 window_size=ImGui::GetWindowSize();
    int texture_per_line=ceil(float(DRUM_IMAGES_AMOUNT)/2.0f);
    int h_texture_size=(window_size.x-(INFO_SPACER*texture_per_line*2))/texture_per_line;
    int v_texture_size=((window_size.y-WINDOW_TOP_SPACER.y)-(INFO_SPACER*4))/2;


    int selected_texture_size;
    //selecting smalest of possible squeres
    if(h_texture_size>v_texture_size){
        selected_texture_size=v_texture_size;
    }
    else{
        selected_texture_size=h_texture_size;
    }

    //Drawing first raw of textures
    for (int i = 0; i < texture_per_line; i++)
    {
        ImGui::SetCursorPos(ImVec2(INFO_SPACER+(INFO_SPACER*i)+(i*selected_texture_size), INFO_SPACER)+WINDOW_TOP_SPACER);
        ImGui::Image((ImTextureID)(intptr_t)loaded_list[i].texture_data, ImVec2(selected_texture_size, selected_texture_size));
        if(ImGui::IsItemHovered()){
            
            q_tip=loaded_list[i].score;

        }      
    }

    //Drawin second raw of textures
    for(int i=texture_per_line; i<DRUM_IMAGES_AMOUNT; i++){
        ImGui::SetCursorPos(ImVec2(INFO_SPACER+(INFO_SPACER*(i-texture_per_line))+((i-texture_per_line)*selected_texture_size), (INFO_SPACER*2)+selected_texture_size)+WINDOW_TOP_SPACER);
        ImGui::Image((ImTextureID)(intptr_t)loaded_list[i].texture_data, ImVec2(selected_texture_size, selected_texture_size));
        if(ImGui::IsItemHovered()){

            q_tip=loaded_list[i].score;
            
        }      
    }


    //Display tooltip, if requested
    if(q_tip!=0){
        ImGui::Text("Symbol score: x%.1f", q_tip);
        q_tip=0;    
    }
    
    

}
