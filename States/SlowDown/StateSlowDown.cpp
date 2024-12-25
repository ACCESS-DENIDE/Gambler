#include "StateSlowDown.hpp"

ACD::StateSlowDown::StateSlowDown()
{
    my_state_id=3;
    next_state_id=4;
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
        
        if(!drums[i].GetState(nullptr)){
            return 0;
        }
    }
      
    
    return 1;
}

ACD::StateSlowDown::~StateSlowDown()
{

}
