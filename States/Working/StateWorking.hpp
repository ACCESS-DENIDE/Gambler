#ifndef STATE_WORK
#define STATE_WORK

#include "../../Classes/StateMachine/StateMachine.hpp"

namespace ACD
{
    /// @brief Class for processing Working(spinning) state
    class StateWorking:public StateMachine
    {
    private:
        
    public:
        StateWorking();
        int OnSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
        int Frame(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
        int OutSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
        ~StateWorking();
    };
    
}

#endif