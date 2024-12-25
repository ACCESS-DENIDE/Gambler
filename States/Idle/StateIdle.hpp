#ifndef STATE_IDLE
#define STATE_IDLE

#include "../../Classes/StateMachine/StateMachine.hpp"

namespace ACD
{
    /// @brief Class for processing Idle state
    class StateIdle:public StateMachine
    {
    private:
        
    public:
        StateIdle();
        int OnSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
        int Frame(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
        int OutSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
        ~StateIdle(){};
    };
    
}

#endif