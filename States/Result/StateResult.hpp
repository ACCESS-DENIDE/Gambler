#ifndef STATE_RESULT
#define STATE_RESULT





#include "../../Classes/StateMachine/StateMachine.hpp"

namespace ACD
{
    class StateResult:public StateMachine
    {
    private:

    int * calc_bet;
    int calc_win;

    public:
        StateResult();
        int OnSwitch(Drum drums[DRUMS_AMOUNT]);
        int Frame(Drum drums[DRUMS_AMOUNT]);
        void SetCalcBet(int* new_calc_bet);
        int OutSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
        ~StateResult();
    };
    
}

#endif