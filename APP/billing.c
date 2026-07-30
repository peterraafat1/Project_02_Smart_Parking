#include "billing.h"

uint16_t BIL_Compute(uint32_t entrySec, uint32_t exitSec, uint8_t tariffPerHour, uint8_t graceMinutes) {
    if (exitSec <= entrySec) {
        return 0;
    }
    
    uint32_t dwellSec = exitSec - entrySec;
    uint32_t dwellMin = dwellSec / 60;
    
    if (dwellMin <= graceMinutes) {
        return 0;
    }
    
    uint32_t chargeableMin = dwellMin - graceMinutes;
    uint32_t hours = chargeableMin / 60;
    
    if ((chargeableMin % 60) > 0) {
        hours++;
    }
    
    uint32_t fee = hours * tariffPerHour;
    
    if (fee > 120) {
        fee = 120;
    }
    
    return (uint16_t)fee;
}