#include "StateMachine.hpp"

void ACD::StateMachine::SetDisplayName(const char *new_displayname)
{
    int cou=-1;

    do{
        cou++;
    }while(new_displayname[cou]!='\0');
    display_size=cou+1;
    display_state=new char[display_size];

    for (int i=0; i<display_size; i++){
        display_state[i]=new_displayname[i];
    }

    
}

ACD::StateMachine::StateMachine()
{
}

ACD::StateMachine::~StateMachine()
{
    if(display_state!=nullptr){
        delete [] display_state;
    }
    
}
ACD::StateMachine &ACD::StateMachine::operator=(const StateMachine &right)
{
    display_size=right.display_size;
    next_state_id=right.next_state_id;
    my_state_id=right.my_state_id;

    int cou=-1;

    do{
        cou++;
    }while(right.display_state[cou]!='\0');
    display_size=cou+1;
    display_state=new char[display_size];

    for (int i=0; i<display_size; i++){
        display_state[i]=right.display_state[i];
    }

    return *this;
}
bool ACD::StateMachine::IsValidStateSwitch(int new_state_id)
{
    return (new_state_id==next_state_id);
}

char *ACD::StateMachine::GetDisplayState(int * size)
{
    if(size!=nullptr){
        (*size)=display_size;
    }
    return display_state;
}

int ACD::StateMachine::GetStateId()
{
    return my_state_id;
}
