#include "../Service/STD_Types.h"
#include "../APP/lane_fsm.h"

volatile uint16_t tick_10ms = 0;
volatile uint16_t tick_50ms = 0;
volatile uint16_t tick_250ms = 0;
volatile uint16_t tick_1s = 0;
volatile uint16_t tick_5s = 0;

void System_Init(void) {
    
    LANE_Init(&g_entryLane, 1, 1); 
    LANE_Init(&g_exitLane, 2, 0);  
}

int main(void) {
    System_Init();
    
    while (1) {
        if (tick_10ms >= 1) {
            tick_10ms = 0;
            LANE_Run(&g_entryLane);
            LANE_Run(&g_exitLane);
        }
        
        if (tick_50ms >= 5) {
            tick_50ms = 0;
        }
        
        if (tick_250ms >= 25) {
            tick_250ms = 0;
        }
        
        if (tick_1s >= 100) {
            tick_1s = 0;
        }
        
        if (tick_5s >= 500) {
            tick_5s = 0;
        }
    }
    return 0;
}