#include "monitor.h"
PC_Monitor monitor_pc(Status s,Frame * sent_Frames , Frame * received_Frames)
{
    PC_Monitor m;
    /* getting the current state of the PC */
    m.state = s.get_state();
    /* getting the number of frames sent by the PC */
    m.no_Of_Frames_sent = s.get_number_of_frames();
    // we need to get number of frames received by the PC
    
    /* getting the size of each frame sent by the PC and the number of each frame*/
    // kda el ragel hyb2a m3ah access 3la array gwah el frames number w size
    m.frames_Sent = sent_Frames;    
    
    // getting the size of each frame received by the PC 
    m.frames_Received = received_Frames;
}