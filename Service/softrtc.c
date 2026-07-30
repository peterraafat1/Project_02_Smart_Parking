#include "softrtc.h"

volatile uint32_t g_uptimeSec = 0;

void RTC_Init(void) {
    g_uptimeSec = 0;
}

void RTC_Tick(void) {
    g_uptimeSec++;
}