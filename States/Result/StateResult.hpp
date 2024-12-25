#ifndef STATE_RESULT
#define STATE_RESULT





#include "../../Classes/StateMachine/StateMachine.hpp"

namespace ACD
{
    /// @brief Class for processing Result showing state
    class StateResult:public StateMachine
    {
    private:

    /// @brief reference to player's bet
    int * calc_bet;
    /// @brief calculated player's win
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