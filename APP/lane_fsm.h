#ifndef LANE_FSM_H
#define LANE_FSM_H

#include "../Service/STD_Types.h"

typedef enum { 
    LN_IDLE = 0, 
    LN_VEHICLE_WAIT, 
    LN_AUTHORISING,
    LN_GATE_OPENING, 
    LN_GATE_OPEN, 
    LN_VEHICLE_PASSING,
    LN_GATE_CLOSING, 
    LN_REJECTED, 
    LN_TIMEOUT 
} LaneState_t;

typedef struct {
    LaneState_t state;      
    uint16_t    timerTicks; 
    uint8_t     loopActive;  
    uint8_t     servoCh;     
    uint8_t     isEntry;    
    uint16_t    passCount;   
    uint8_t     faultFlag;  
} Lane_t;

extern Lane_t g_entryLane;
extern Lane_t g_exitLane;

void LANE_Init(Lane_t *ln, uint8_t servoCh, uint8_t isEntry);
void LANE_Run(Lane_t *ln);

#endif /* LANE_FSM_H */