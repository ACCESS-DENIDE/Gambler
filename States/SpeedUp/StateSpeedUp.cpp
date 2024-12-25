#include "StateSpeedUp.hpp"

ACD::StateSpeedUp::StateSpeedUp()
{
    my_state_id=SpeedUp;
    next_state_id=Work;
    SetDisplayName("Speed Up");
}

int ACD::StateSpeedUp::OnSwitch(Drum drums[DRUMS_AMOUNT])
{
    for (int i = 0; i < DRUMS_AMOUNT; i++)
    {
        drums[i].Start();
    }
    
    return 0;
}

int ACD::StateSpeedUp::Frame(Drum drums[DRUMS_AMOUNT])
{

    for (int i = 0; i < DRUMS_AMOUNT; i++)
    {
        
        if(!drums[i].GetState()){
            return 0;
        }
    }
      
    
    return 1;
}

ACD::StateSpeedUp::~StateSpeedUp()
{
}
