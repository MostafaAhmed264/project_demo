#ifndef DATE_H
#define DATE_H

typedef enum{
    IDLE, ACTIVE 
}State; 

class Status{ 
    private: 
        State state; 
        long long number_of_frames;
    public: 
    /*
        Consructors and destructor of the Class
    */
        Status(State state, long long number); 
        ~Status(); 
    /*
        Accessors
    */
        State get_state(void);
        long long get_number_of_frames(void);
    /*
        Mutators
    */
        void set_state(State s);
        void set_number_of_frames (long long n);
}; 

#endif