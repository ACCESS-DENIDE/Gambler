#include "../Classes/GUI/GUI.hpp"

#include <iostream>
void TestProbe();
bool AddSymb(int symb_num, int* arr);


int main(int args_cou, char** args)
{

    if(args_cou>1)
    {
        if(args[1][0]=='-' && args[1][1]=='t' && args[1][2]=='\0')
        {
            TestProbe();
        }
    }
    else
    {
        ACD::GUI test_gui=ACD::GUI(960, 540, "Gambler");
        test_gui.Launch();
    }


  
    return 0;
}


void TestProbe(){

    ACD::GUI probe;
    bool is_working=true;
    int symb_counter[DRUMS_AMOUNT];

    for (int i = 0; i < DRUMS_AMOUNT; i++)
    {
        symb_counter[i]=0;
    }
    

    ACD::LoadDrumImages();

    ACD::TextureInfo* loaded_symbs=ACD::GetArrBegin();

    double aver=loaded_symbs[0].score*DRUMS_AMOUNT;

    long long int cou=1;
    AddSymb(0,  &symb_counter[0]);
    do
    {
        cou++;
        float multip_arr[DRUMS_AMOUNT];
        int multip_cou=0;
        int prev_ref=0;
        float full_multip=1;

        for (int i=0; i<DRUMS_AMOUNT; i++){
            multip_arr[i]=1;
        }

        multip_arr[0]=loaded_symbs[symb_counter[0]].score;
        prev_ref=symb_counter[0];

        for (int i = 1; i < DRUMS_AMOUNT; i++)
        {

            if(prev_ref==symb_counter[i]){
                multip_arr[multip_cou]+=loaded_symbs[symb_counter[i]].score;
            }
            else
            {
                multip_cou++;
                multip_arr[multip_cou]=loaded_symbs[symb_counter[i]].score;
                prev_ref=symb_counter[i];
            }
            
        }

        for (int i = 0; i < DRUMS_AMOUNT; i++)
        {
            full_multip*=multip_arr[i];
        }
        

        
        aver+=full_multip;

        is_working=AddSymb(0, &symb_counter[0]);
    } while (is_working);

    aver=aver/cou;
    
    std:: cout<<"Found "<<cou<<" solutions with average multiplyer: "<<aver<<'\n';

}
bool AddSymb(int symb_num, int* arr)
{
    if(symb_num>=DRUMS_AMOUNT){
        return false;
    }
    arr[symb_num]++;

    if(arr[symb_num]>=DRUM_IMAGES_AMOUNT){
        arr[symb_num]=0;
        return AddSymb(symb_num+1, arr);
    }

    return true;

};