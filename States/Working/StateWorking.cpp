#include "StateWorking.hpp"

ACD::StateWorking::StateWorking()
{
    my_state_id=Work;
    next_state_id=SlowDown;
    SetDisplayName("Working");
}

ACD::StateWorking::~StateWorking()
{
}
