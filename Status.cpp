#include "Status.h"

/*
    Constructor implementation 
*/
Status ::Status(State state, long long number){ 
    this->state = state; 
    this ->number_of_frames = number; 
}


/*
    Mutators implemantion
*/

void Status :: set_state(State s){ 
    this->state = s; 
}

void Status :: set_number_of_frames(long long n){
    this->number_of_frames = n; 
}

/*
    Accessors implementation
*/

State Status :: get_state(){
    return this->state; 
}

long long Status :: get_number_of_frames(){
    return this->number_of_frames; 
}