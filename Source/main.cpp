#include "../Classes/GUI/GUI.hpp"

//used for print output of test probe
#include <iostream>
//used for generate seed in random
#include <ctime>
//used for Ini file creation
#include <fstream>

/// @brief Provides test info about average winrate
void TestProbe();

/// @brief Internal function to change number of element on test probe
/// @param symb_num number to increase
/// @param arr pointer to array of symbols
/// @return false, if all symbols checked, true otherwise
bool AddSymb(int symb_num, int* arr);

/// @brief Generate subwindows layout file for im'gui, if does not exist
void GenerateIni();

int main(int args_cou, char** args)
{

    GenerateIni();
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

}
void GenerateIni() {
    std::ifstream fin;
    std::ofstream fout;

    //Checking, if file exist
    fin.open("imgui.ini");
    if(fin.good()){
        return;
    }

    fin.close();

//if it's not, load default layout
    fout.open("imgui.ini");

    fout<<"[Window][Debug##Default]\n \
Pos=0,0\n \
Size=960,540\n \
Collapsed=0\n\n";

fout<<"[Window][Bank]\n\
Pos=714,233\n\
Size=246,158\n\
Collapsed=0\n\
DockId=0x00000006,0\n\n";

    fout<<"[Window][Control Panel]\n\
Pos=714,0\n\
Size=246,231\n\
Collapsed=0\n\
DockId=0x00000005,0\n\n";

    fout<<"[Window][OpenGL Texture Text]\n\
Pos=90,106\n\
Size=357,270\n\
Collapsed=0\n\n";

    fout<<"[Window][RESULTS]\n\
Pos=233,175\n\
Size=170,65\n\
Collapsed=0\n\n";

fout<<"[Window][WindowOverViewport_11111111]\n\
Pos=0,0\n\
Size=960,540\n\
Collapsed=0\n\n";

fout<<"[Window][Info]\n\
Pos=0,393\n\
Size=960,147\n\
Collapsed=0\n\
DockId=0x0000000A,0\n\n";

fout<<"[Window][Drums]\n\
Pos=0,0\n\
Size=712,391\n\
Collapsed=0\n\
DockId=0x00000007,0\n\n";


    fout<<"[Docking][Data]\n\
DockSpace           ID=0x08BD597D Window=0x1BBC0F80 Pos=0,0 Size=960,540 Split=Y Selected=0x2C02F5A4\n\
  DockNode          ID=0x00000009 Parent=0x08BD597D SizeRef=960,391 Split=X\n\
    DockNode        ID=0x00000001 Parent=0x00000009 SizeRef=477,540 Selected=0x2C02F5A4\n\
    DockNode        ID=0x00000002 Parent=0x00000009 SizeRef=481,540 Split=Y Selected=0x2E82A93E\n\
      DockNode      ID=0x00000003 Parent=0x00000002 SizeRef=820,356 Split=X Selected=0x2E82A93E\n\
        DockNode    ID=0x00000007 Parent=0x00000003 SizeRef=712,336 CentralNode=1 Selected=0x2E82A93E\n\
        DockNode    ID=0x00000008 Parent=0x00000003 SizeRef=246,336 Split=Y Selected=0xD8767A6B\n\
          DockNode  ID=0x00000005 Parent=0x00000008 SizeRef=344,231 Selected=0xF930105C\n\
          DockNode  ID=0x00000006 Parent=0x00000008 SizeRef=344,158 Selected=0xD8767A6B\n\
      DockNode      ID=0x00000004 Parent=0x00000002 SizeRef=820,182 Selected=0x928212AD\n\
  DockNode          ID=0x0000000A Parent=0x08BD597D SizeRef=960,147 Selected=0x928212AD\n\
";

    fout.close();

};