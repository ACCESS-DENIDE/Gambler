#include "StateResult.hpp"


ACD::StateResult::StateResult()
{
    my_state_id=Result;
    next_state_id=Idle;
    SetDisplayName("Results");
    calc_win=0;
    calc_bet=nullptr;

}

int ACD::StateResult::OnSwitch(Drum drums[DRUMS_AMOUNT])
{
    //Check, if player's bet connected
    assert(calc_bet!=nullptr);
    //Creating default variables
    float multip_arr[DRUMS_AMOUNT];
    int multip_cou=0;
    GLuint prev_ref=0;
    float score_buff=0;
    GLuint ref_buff=0;
    float full_multip=1;
    
    //Cleaning created arr
    for (int i=0; i<DRUMS_AMOUNT; i++){
        multip_arr[i]=1;
    }


    //Storing first drum value to start
    drums[0].GetState(&score_buff, &prev_ref);

    multip_arr[0]=score_buff;

    //Processing other drums
    for (int i = 1; i < DRUMS_AMOUNT; i++)
    {
        //Read data from drum
        drums[i].GetState(&score_buff, &ref_buff);
        //Check, if symbol equal to previous symbol
        if(prev_ref==ref_buff){
            //if equal, add score to current multiplyer
            multip_arr[multip_cou]+=score_buff;
        }
        else
        {   
            //If symol changed, start new multiplyer
            multip_cou++;
            multip_arr[multip_cou]=score_buff;
            prev_ref=ref_buff;
        }
        
    }

    //Multiply all multiplyers
    for (int i = 0; i < DRUMS_AMOUNT; i++)
    {
        full_multip*=multip_arr[i];
    }

    //Multiply player's bet to the total multiplyer (cause the house always wins.)
    calc_win=floor(float((*calc_bet))*full_multip);


    return 0;
}

int ACD::StateResult::Frame(Drum drums[DRUMS_AMOUNT])
{
    return calc_win;
}

void ACD::StateResult::SetCalcBet(int *new_calc_bet)
{
    calc_bet=new_calc_bet;
}

ACD::StateResult::~StateResult()
{

}
