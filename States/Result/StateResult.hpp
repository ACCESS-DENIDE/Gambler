#ifndef STATE_RESULT
#define STATE_RESULT





#include "../../Classes/StateMachine/StateMachine.hpp"

namespace ACD
{
    class StateResult:public StateMachine
    {
    private:

    public:
        StateResult();
        int OnSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
        int Frame(Drum drums[DRUMS_AMOUNT]);
        int OutSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
        ~StateResult();
    };
    
}

#endif