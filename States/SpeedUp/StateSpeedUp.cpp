#include "StateSpeedUp.hpp"

ACD::StateSpeedUp::StateSpeedUp()
{
    my_state_id=SpeedUp;
    next_state_id=Work;
    SetDisplayName("Speed Up");
}

int ACD::StateSpeedUp::OnSwitch(Drum drums[DRUMS_AMOUNT])
{

    //On start send speed up command to all drums
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
        
        //Check, if all drums max speed
        if(!drums[i].GetState()){
            //if not, send error
            return 0;
        }
    }
      
    
    return 1;
}

ACD::StateSpeedUp::~StateSpeedUp()
{
}
