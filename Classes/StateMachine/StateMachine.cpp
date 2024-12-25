#include "StateMachine.hpp"

/// @brief Set display status name
/// @param new_displayname New value to show in "Current state"
void ACD::StateMachine::SetDisplayName(const char *new_displayname)
{
    int cou=-1;

    //Get input size
    do{
        cou++;
    }while(new_displayname[cou]!='\0');
    //Allocate and copy memory
    display_size=cou+1;
    display_state=new char[display_size];

    for (int i=0; i<display_size; i++){
        display_state[i]=new_displayname[i];
    }

    
}


/// @brief Deconstractor for any state (deallocation of display_name)
ACD::StateMachine::~StateMachine()
{
    if(display_state!=nullptr){
        delete [] display_state;
    }
    
}
/// @brief StateMachine assignment operator
/// @param right sourse of assignment
/// @return copied StateMachine
ACD::StateMachine &ACD::StateMachine::operator=(const StateMachine &right)
{
    //Copy all data, except pointers
    display_size=right.display_size;
    next_state_id=right.next_state_id;
    my_state_id=right.my_state_id;

    int cou=-1;

    //Copy pointer content
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

/// @brief Check, can this state switch to provided state
/// @param new_state_id Possible next state
/// @return True, if State switch is valid, false otherwise
bool ACD::StateMachine::IsValidStateSwitch(int new_state_id)
{
    return (new_state_id==next_state_id);
}

/// @brief Provides pointer to display_name of state
/// @param size pointer to storage for size of display_name
/// @return pointer to begining of display_state
const char *ACD::StateMachine::GetDisplayState(int * size)
{
    //if requested, return char* size
    if(size!=nullptr){
        (*size)=display_size;
    }
    return display_state;
}

/// @brief Returns this state identifier
/// @return state ID
int ACD::StateMachine::GetStateId()
{
    return my_state_id;
}
