#include "StateIdle.hpp"

ACD::StateIdle::StateIdle()
{
    my_state_id=Idle;
    next_state_id=SpeedUp;
    SetDisplayName("Idle");
}
