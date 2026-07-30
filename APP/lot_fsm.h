#ifndef LOT_FSM_H
#define LOT_FSM_H

#include "../Service/STD_Types.h"

typedef enum { 
    LOT_INIT = 0, 
    LOT_OPERATIONAL, 
    LOT_FULL,
    LOT_MAINTENANCE, 
    LOT_FAULT 
} LotState_t;

extern LotState_t g_lotState;

void LOT_Init(void);
void LOT_Run(void);
void LOT_ToggleMaintenance(void);

#endif