#include "../Classes/GUI/GUI.hpp"

//used for print output of test probe
#include <iostream>
//used for generate seed in random
#include <ctime>

/// @brief Provides test info about average winrate
void TestProbe();

/// @brief Internal function to change number of element on test probe
/// @param symb_num number to increase
/// @param arr pointer to array of symbols
/// @return false, if all symbols checked, true otherwise
bool AddSymb(int symb_num, int* arr);


int main(int args_cou, char** args)
{


    //If detects additional input, switch to service mode
    if(args_cou>1)
    {
        //If propper service mode, calculate average win
        if(args[1][0]=='-' && args[1][1]=='t' && args[1][2]=='\0')
        {
            TestProbe();
            return 0;
        }
        else{
            //If wrong service mode, exit with error
            std::cout<<"Error, unknown input.\n";
            return -1;
        }
    }
    else
    {
        //If no service mode, normal launch
        ACD::Seed(std::time(nullptr));
        ACD::GUI test_gui=ACD::GUI(960, 540, "Gambler");
        test_gui.Launch();
    }


  
    return 0;
}


void TestProbe(){

    //Construct GUI for OpenGL initialization
    ACD::GUI probe;
    //Creating working variables
    bool is_working=true;
    int symb_counter[DRUMS_AMOUNT];

    //Clearing array
    for (int i = 0; i < DRUMS_AMOUNT; i++)
    {
        symb_counter[i]=0;
    }
    
    //Load images to VRAM
    ACD::LoadDrumImages();

    //Connecting probe array to texture loader
    ACD::TextureInfo* loaded_symbs=ACD::GetArrBegin();

    
    double aver=loaded_symbs[0].score*DRUMS_AMOUNT;
    long long int cou=1;
    AddSymb(0,  &symb_counter[0]);
    
    //Checking all coombinations and summarize all multiplyers
    do
    {
        cou++;
        float multip_arr[DRUMS_AMOUNT];
        int multip_cou=0;
        int prev_ref=0;
        float full_multip=1;

        //Calculate configuration

        for (int i=0; i<DRUMS_AMOUNT; i++){
            multip_arr[i]=1;
        }

        multip_arr[0]=loaded_symbs[symb_counter[0]].score;
        prev_ref=symb_counter[0];

        for (int i = 1; i < DRUMS_AMOUNT; i++)
        {
            //If same as previos, add to curent
            if(prev_ref==symb_counter[i]){
                //If same as previos, add to curent
                multip_arr[multip_cou]+=loaded_symbs[symb_counter[i]].score;
            }
            else
            {
                //If different from prev, start new multiplyer
                multip_cou++;
                multip_arr[multip_cou]=loaded_symbs[symb_counter[i]].score;
                prev_ref=symb_counter[i];
            }
            
        }

        //Multiply all multypliers
        for (int i = 0; i < DRUMS_AMOUNT; i++)
        {
            full_multip*=multip_arr[i];
        }
        

        
        aver+=full_multip;
        //Generating new configuration
        is_working=AddSymb(0, &symb_counter[0]);
    } while (is_working);

    //Calculating average value
    aver=aver/cou;
    
    std:: cout<<"Found "<<cou<<" solutions with average multiplyer: "<<aver<<'\n';

}
bool AddSymb(int symb_num, int* arr)
{
    //If reached maximum layer, return false
    if(symb_num>=DRUMS_AMOUNT){
        return false;
    }
    arr[symb_num]++;

    //if reached maximum on this layer, send carry to the next layer
    if(arr[symb_num]>=DRUM_IMAGES_AMOUNT){
        arr[symb_num]=0;
        return AddSymb(symb_num+1, arr);
    }

    return true;

};