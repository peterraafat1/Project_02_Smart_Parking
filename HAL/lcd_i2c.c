#include "../Service/STD_Types.h"
#include "../Service/Bit_Math.h"
#include <avr/io.h>

extern void I2C_Start(void);
extern void I2C_Stop(void);
extern void I2C_Write(uint8_t data);

#define LCD_ADDR 0x4E

void LCD_WriteNibble(uint8_t nibble, uint8_t rs) {
    uint8_t data = (nibble << 4) | (rs << 0) | (1 << 3);
    I2C_Start();
    I2C_Write(LCD_ADDR);
    I2C_Write(data | (1 << 2));
    I2C_Write(data & ~(1 << 2));
    I2C_Stop();
}

void LCD_WriteCmd(uint8_t cmd) {
    LCD_WriteNibble(cmd >> 4, 0);
    LCD_WriteNibble(cmd & 0x0F, 0);
}

void LCD_WriteData(uint8_t data) {
    LCD_WriteNibble(data >> 4, 1);
    LCD_WriteNibble(data & 0x0F, 1);
}

void LCD_Init(void) {
    LCD_WriteCmd(0x02);
    LCD_WriteCmd(0x28);
    LCD_WriteCmd(0x0C);
    LCD_WriteCmd(0x01);
}

void LCD_Print(const char *str) {
    while (*str) {
        LCD_WriteData((uint8_t)*str++);
    }
}