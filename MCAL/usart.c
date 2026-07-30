#include "../Service/STD_Types.h"
#include <avr/io.h>

void USART_Init(void) {
    uint16_t ubrr = 51;
    UBRRH = (uint8_t)(ubrr >> 8);
    UBRRL = (uint8_t)ubrr;
    UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void USART_Transmit(uint8_t data) {
    while (!(UCSRA & (1 << UDRE)));
    UDR = data;
}

void USART_PrintString(const char *str) {
    while (*str) {
        USART_Transmit((uint8_t)*str++);
    }
}