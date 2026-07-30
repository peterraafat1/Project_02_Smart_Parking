#ifndef SOFTRTC_H
#define SOFTRTC_H

#include "STD_Types.h"

extern volatile uint32_t g_uptimeSec;

void RTC_Init(void);
void RTC_Tick(void);

#endif