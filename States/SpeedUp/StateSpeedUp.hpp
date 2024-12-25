#ifndef STATE_SPEED
#define STATE_SPEED

#include "../../Classes/StateMachine/StateMachine.hpp"

namespace ACD
{

    /// @brief Class for processing SpeedUp state
    class StateSpeedUp:public StateMachine
    {
    private:
        
    public:
        StateSpeedUp();
        int OnSwitch(Drum drums[DRUMS_AMOUNT]);
        int Frame(Drum drums[DRUMS_AMOUNT]);
        int OutSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
        ~StateSpeedUp();
    };
    
}

#endif