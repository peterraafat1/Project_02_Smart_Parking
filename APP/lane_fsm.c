#include "lane_fsm.h"

#define TICKS_200MS          20
#define GATE_TRAVEL_TICKS    100   
#define GATE_HOLD_TICKS      500   
#define PASS_TIMEOUT_TICKS   2000  
#define REJECT_TICKS         200   

extern uint8_t LOT_GetFree(void);
extern void BAR_Open(uint8_t ch);
extern void BAR_Close(uint8_t ch);

Lane_t g_entryLane;
Lane_t g_exitLane;

void LANE_Init(Lane_t *ln, uint8_t servoCh, uint8_t isEntry) {
    ln->state = LN_IDLE;
    ln->timerTicks = 0;
    ln->loopActive = 0;
    ln->servoCh = servoCh;
    ln->isEntry = isEntry;
    ln->passCount = 0;
    ln->faultFlag = 0;
}

void LANE_Run(Lane_t *ln) {
    if (ln->timerTicks > 0) {
        ln->timerTicks--;
    }

    switch (ln->state) {
        case LN_IDLE:
            if (ln->loopActive) {
                ln->timerTicks = TICKS_200MS;
                ln->state = LN_VEHICLE_WAIT;
            }
            break;

        case LN_VEHICLE_WAIT:
            if (ln->timerTicks == 0) {
                ln->state = LN_AUTHORISING;
            }
            break;

        case LN_AUTHORISING:
            if (ln->isEntry && LOT_GetFree() == 0) {
                ln->timerTicks = REJECT_TICKS;
                ln->state = LN_REJECTED;
            } else {
                BAR_Open(ln->servoCh);
                ln->timerTicks = GATE_TRAVEL_TICKS;
                ln->state = LN_GATE_OPENING;
            }
            break;

        case LN_REJECTED:
            if (ln->timerTicks == 0) {
                ln->state = LN_IDLE;
            }
            break;

        case LN_GATE_OPENING:
            if (ln->timerTicks == 0) {
                ln->timerTicks = GATE_HOLD_TICKS;
                ln->state = LN_GATE_OPEN;
            }
            break;

        case LN_GATE_OPEN:
            if (ln->loopActive) {
                ln->timerTicks = PASS_TIMEOUT_TICKS;
                ln->state = LN_VEHICLE_PASSING;
            } else if (ln->timerTicks == 0) {
                BAR_Close(ln->servoCh);
                ln->timerTicks = GATE_TRAVEL_TICKS;
                ln->state = LN_GATE_CLOSING;
            }
            break;

        case LN_VEHICLE_PASSING:
            if (!ln->loopActive) {
                ln->passCount++;
                BAR_Close(ln->servoCh);
                ln->timerTicks = GATE_TRAVEL_TICKS;
                ln->state = LN_GATE_CLOSING;
            } else if (ln->timerTicks == 0) {
                BAR_Close(ln->servoCh);
                ln->faultFlag = 1;
                ln->state = LN_TIMEOUT;
            }
            break;

        case LN_GATE_CLOSING:
            if (ln->timerTicks == 0) {
                ln->state = LN_IDLE;
            }
            break;

        case LN_TIMEOUT:
            if (!ln->loopActive) {
                ln->faultFlag = 0;
                ln->state = LN_IDLE;
            }
            break;
    }
}