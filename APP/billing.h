#ifndef BILLING_H
#define BILLING_H

#include "../Service/STD_Types.h"

uint16_t BIL_Compute(uint32_t entrySec, uint32_t exitSec, uint8_t tariffPerHour, uint8_t graceMinutes);

#endif