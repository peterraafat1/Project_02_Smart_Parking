#include "../Service/STD_Types.h"
#include "../Service/Bit_Math.h"
#include <avr/io.h>

void SEG7_Init(void) {
    DDRB |= 0x0F;
}

void SEG7_Show(uint8_t num) {
    if (num > 9) return;
    PORTB = (PORTB & 0xF0) | (num & 0x0F);
}