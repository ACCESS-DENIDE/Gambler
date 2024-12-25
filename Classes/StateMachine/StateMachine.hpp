#ifndef STATEMACHINE_CLASS
#define STATEMACHINE_CLASS

#include "../../GUIunits/Drum/Drum.hpp"

namespace ACD
{
    /// @brief All provided states in this state machine
    enum States:int{
        Idle=0,
        SpeedUp,
        Work,
        SlowDown,
        Result
    };
    /// @brief Base class for all states in this state machine
    class StateMachine
    {
        private:
            /// @brief pointer to allocated memory for DisplayName of state
            char* display_state;
            /// @brief Size of allocated memory for DisplayName
            int display_size;


        protected:
            /// @brief Current state ID
            States next_state_id;
            /// @brief Valid next state ID
            States my_state_id;
            
            void SetDisplayName(const char* new_displayname);
            

        public:
            StateMachine(){};
            bool IsValidStateSwitch(int new_state_id);
            const char* GetDisplayState(int * size=nullptr);
            int GetStateId();
            /// @brief Called when StateMachine switches to this state
            /// @param drums array of all drums in slot machine
            /// @return return code
            virtual int OnSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};

            /// @brief Called every frame
            /// @param drums array of all drums in slot machine
            /// @return return code
            virtual int Frame(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
            
            /// @brief Called when StateMachine switches out of this state
            /// @param drums array of all drums in slot machine
            /// @return return code
            virtual int OutSwitch(Drum drums[DRUMS_AMOUNT]){/*NOTHING SPECIAL*/ return 0;};
            ~StateMachine();

            StateMachine& operator=(const StateMachine& right);
    };
       
}
#endif

