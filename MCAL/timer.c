#include "../Service/STD_Types.h"
#include "../Service/Bit_Math.h"
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile uint16_t tick_10ms;
extern volatile uint16_t tick_50ms;
extern volatile uint16_t tick_250ms;
extern volatile uint16_t tick_1s;
extern volatile uint16_t tick_5s;

void Timer0_Init(void) {
    TCCR0 = (1 << WGM01) | (1 << CS02) | (1 << CS00);
    OCR0 = 77;
    TIMSK |= (1 << OCIE0);
}

ISR(TIMER0_COMP_vect) {
    tick_10ms++;
    tick_50ms++;
    tick_250ms++;
    tick_1s++;
    tick_5s++;
}