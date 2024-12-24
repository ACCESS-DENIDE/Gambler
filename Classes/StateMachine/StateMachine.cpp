#include "StateMachine.hpp"

bool ACD::StateMachine::IsValidStateSwitch(int new_state_id)
{
    return (new_state_id==next_state_id);
}
