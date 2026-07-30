#include "../Service/STD_Types.h"
#include <avr/io.h>

#define SLOT_COUNT 6u

uint8_t g_slotMap = 0;
uint8_t g_freeCount = 6;
uint8_t g_occupiedCount = 0;

void SLOTS_Init(void) {
    DDRC &= ~0xFC; 
    PORTC |= 0xFC; 
}

static uint8_t popcount6(uint8_t m) {
    m = (uint8_t)(m - ((m >> 1) & 0x55u));
    m = (uint8_t)((m & 0x33u) + ((m >> 2) & 0x33u));
    return (uint8_t)((m + (m >> 4)) & 0x0Fu);
}

void SLOTS_Poll(void) {
    uint8_t current_pins = (~PINC >> 2) & 0x3F;
    
    g_slotMap = current_pins;
    
    g_occupiedCount = popcount6(g_slotMap);
    g_freeCount = (uint8_t)(SLOT_COUNT - g_occupiedCount);
}

uint8_t LOT_GetFree(void) {
    return g_freeCount;
}