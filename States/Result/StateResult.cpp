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
    assert(calc_bet!=nullptr);
    float multip_arr[DRUMS_AMOUNT];
    int multip_cou=0;
    GLuint prev_ref=0;
    float score_buff=0;
    GLuint ref_buff=0;
    float full_multip=1;
    
    for (int i=0; i<DRUMS_AMOUNT; i++){
        multip_arr[i]=1;
    }

    drums[0].GetState(&score_buff, &prev_ref);

    multip_arr[0]=score_buff;

    for (int i = 1; i < DRUMS_AMOUNT; i++)
    {
        drums[i].GetState(&score_buff, &ref_buff);
        if(prev_ref==ref_buff){
            multip_arr[multip_cou]+=score_buff;
        }
        else
        {
            multip_cou++;
            multip_arr[multip_cou]=score_buff;
            prev_ref=ref_buff;
        }
        
    }

    
    for (int i = 0; i < DRUMS_AMOUNT; i++)
    {
        full_multip*=multip_arr[i];
    }

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
