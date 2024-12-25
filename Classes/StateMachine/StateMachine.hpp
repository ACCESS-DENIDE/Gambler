#ifndef STATEMACHINE_CLASS
#define STATEMACHINE_CLASS

#include "../../GUIunits/Drum/Drum.hpp"

namespace ACD
{
    enum States:int{
        Idle=0,
        SpeedUp,
        Work,
        SlowDown,
        Result
    };
    class StateMachine
    {
        private:
            char* display_state;
            int display_size;


        protected:
            States next_state_id;
            States my_state_id;
            
            void SetDisplayName(const char* new_displayname);
            

        public:
            StateMachine();
            bool IsValidStateSwitch(int new_state_id);
            const char* GetDisplayState(int * size=nullptr);
            int GetStateId();
            virtual int OnSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
            virtual int Frame(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
            virtual int OutSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
            ~StateMachine();

            StateMachine& operator=(const StateMachine& right);
    };
       
}
#endif