#include "Status.h" 
/* gwah class status ele feh state (Idle , Active) w feh number of frames */
#include "Config_Frame.h"
/* gwah size of frame*/

/*******************************************************************************
 *                                 Definitons                                      
*********************************************************************************/
typedef struct
{
    State state;
    long long no_Of_Frames_sent;
    long long no_Of_Frames_received;
    Frame * frames_Sent;
    Frame * frames_Received;
}PC_Monitor;

typedef struct 
{
    int frameNo;
    int size;
}Frame;         // tfatef ele hymlaha b 7war el dynamic allocation


typedef struct
{
    Status s;
    //complete the struct
}Port_Monitor;

/************************************************************************************
 *                                  Functions
**************************************************************************************/
PC_Monitor monitor_pc();

