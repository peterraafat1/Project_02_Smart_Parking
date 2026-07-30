#include "../Service/STD_Types.h"
#include "../Service/Bit_Math.h"
#include <avr/io.h>

void DIO_SetPinDirection(uint8_t port, uint8_t pin, uint8_t dir) {
    switch (port) {
        case 0: if (dir) DDRA |= (1 << pin); else DDRA &= ~(1 << pin); break;
        case 1: if (dir) DDRB |= (1 << pin); else DDRB &= ~(1 << pin); break;
        case 2: if (dir) DDRC |= (1 << pin); else DDRC &= ~(1 << pin); break;
        case 3: if (dir) DDRD |= (1 << pin); else DDRD &= ~(1 << pin); break;
    }
}

void DIO_SetPinValue(uint8_t port, uint8_t pin, uint8_t val) {
    switch (port) {
        case 0: if (val) PORTA |= (1 << pin); else PORTA &= ~(1 << pin); break;
        case 1: if (val) PORTB |= (1 << pin); else PORTB &= ~(1 << pin); break;
        case 2: if (val) PORTC |= (1 << pin); else PORTC &= ~(1 << pin); break;
        case 3: if (val) PORTD |= (1 << pin); else PORTD &= ~(1 << pin); break;
    }
}

uint8_t DIO_GetPinValue(uint8_t port, uint8_t pin) {
    uint8_t val = 0;
    switch (port) {
        case 0: val = (PINA >> pin) & 0x01; break;
        case 1: val = (PINB >> pin) & 0x01; break;
        case 2: val = (PINC >> pin) & 0x01; break;
        case 3: val = (PIND >> pin) & 0x01; break;
    }
    return val;
}