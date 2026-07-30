#include "../Service/STD_Types.h"
#include "../Service/Bit_Math.h"
#include <avr/io.h>

void SPI_Init(void) {
    DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB7);
    DDRB &= ~(1 << PB6);
    PORTB |= (1 << PB4);
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

uint8_t SPI_Transfer(uint8_t data) {
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}