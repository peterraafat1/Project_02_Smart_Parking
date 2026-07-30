#include "../Service/STD_Types.h"
#include "../Service/Bit_Math.h"
#include <avr/io.h>
#include <avr/interrupt.h>

extern void LANE_RequestExit(void);
extern void LOT_ToggleMaintenance(void);

void EXTI_Init(void) {
    MCUCR |= (1 << ISC01) | (1 << ISC11);
    MCUCR &= ~((1 << ISC00) | (1 << ISC10));
    GICR |= (1 << INT0) | (1 << INT1);
    DDRD &= ~((1 << PD2) | (1 << PD3));
    PORTD |= (1 << PD2) | (1 << PD3);
}

ISR(INT0_vect) {
    LANE_RequestExit();
}

ISR(INT1_vect) {
    LOT_ToggleMaintenance();
}