#include "StateResult.hpp"

ACD::StateResult::StateResult()
{
    my_state_id=4;
    next_state_id=0;
    SetDisplayName("Results");

}

int ACD::StateResult::Frame(Drum drums[DRUMS_AMOUNT])
{
    return 100;
}

ACD::StateResult::~StateResult()
{

}
