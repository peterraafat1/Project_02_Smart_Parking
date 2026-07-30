#include "lot_fsm.h"

extern uint8_t LOT_GetFree(void);
extern void BAR_Open(uint8_t ch);
extern void BAR_Close(uint8_t ch);

LotState_t g_lotState = LOT_INIT;

void LOT_Init(void) {
    g_lotState = LOT_OPERATIONAL;
}

void LOT_Run(void) {
    uint8_t freeSlots = LOT_GetFree();
    
    switch (g_lotState) {
        case LOT_INIT:
            g_lotState = LOT_OPERATIONAL;
            break;
            
        case LOT_OPERATIONAL:
            if (freeSlots == 0) {
                g_lotState = LOT_FULL;
            }
            break;
            
        case LOT_FULL:
            if (freeSlots > 0) {
                g_lotState = LOT_OPERATIONAL;
            }
            break;
            
        case LOT_MAINTENANCE:
            BAR_Open(1);
            BAR_Open(2);
            break;
            
        case LOT_FAULT:
            BAR_Open(1);
            BAR_Open(2);
            break;
    }
}

void LOT_ToggleMaintenance(void) {
    if (g_lotState == LOT_MAINTENANCE) {
        g_lotState = LOT_OPERATIONAL;
        BAR_Close(1);
        BAR_Close(2);
    } else {
        g_lotState = LOT_MAINTENANCE;
    }
}