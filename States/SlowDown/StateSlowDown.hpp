#ifndef STATE_SLOW
#define STATE_SLOW

#include "../../Classes/StateMachine/StateMachine.hpp"

namespace ACD
{

    /// @brief Class for processing SlowDown state
    class StateSlowDown:public StateMachine
    {
    private:
        
    public:
        StateSlowDown();
        int OnSwitch(Drum drums[DRUMS_AMOUNT]);
        int Frame(Drum drums[DRUMS_AMOUNT]);
        int OutSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPETIAL*/ return 0;};
        ~StateSlowDown();
    };
    
}

#endif