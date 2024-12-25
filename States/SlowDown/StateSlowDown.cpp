#include "StateSlowDown.hpp"

ACD::StateSlowDown::StateSlowDown()
{
    my_state_id=SlowDown;
    next_state_id=Result;
    SetDisplayName("Slow down");
}

int ACD::StateSlowDown::OnSwitch(Drum drums[DRUMS_AMOUNT])
{
    for (int i = 0; i < DRUMS_AMOUNT; i++)
    {
        drums[i].Slow();
    }
    
    return 0;
}

int ACD::StateSlowDown::Frame(Drum drums[DRUMS_AMOUNT])
{

    for (int i = 0; i < DRUMS_AMOUNT; i++)
    {
        
        if(!drums[i].GetState()){
            return 0;
        }
    }
      
    
    return 1;
}

ACD::StateSlowDown::~StateSlowDown()
{

}
