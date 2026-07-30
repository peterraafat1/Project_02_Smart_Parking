#include "../Service/STD_Types.h"
#include "../Service/Bit_Math.h"
#include <avr/io.h>

extern uint8_t SPI_Transfer(uint8_t data);

void EEPROM_WriteByte(uint16_t addr, uint8_t data) {
    PORTB &= ~(1 << PB4);
    SPI_Transfer(0x06);
    PORTB |= (1 << PB4);

    PORTB &= ~(1 << PB4);
    SPI_Transfer(0x02);
    SPI_Transfer((uint8_t)(addr >> 8));
    SPI_Transfer((uint8_t)addr);
    SPI_Transfer(data);
    PORTB |= (1 << PB4);

    uint8_t status = 0;
    do {
        PORTB &= ~(1 << PB4);
        SPI_Transfer(0x05);
        status = SPI_Transfer(0xFF);
        PORTB |= (1 << PB4);
    } while (status & 0x01);
}

uint8_t EEPROM_ReadByte(uint16_t addr) {
    PORTB &= ~(1 << PB4);
    SPI_Transfer(0x03);
    SPI_Transfer((uint8_t)(addr >> 8));
    SPI_Transfer((uint8_t)addr);
    uint8_t data = SPI_Transfer(0xFF);
    PORTB |= (1 << PB4);
    return data;
}