#include "../Service/STD_Types.h"
#include <avr/io.h>

void ADC_Init(void) {
    ADMUX = (1 << REFS0);
    
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

uint16_t ADC_Read(uint8_t ch) {
    ch &= 0x07;
    
    ADMUX = (ADMUX & 0xF8) | ch;
    
    ADCSRA |= (1 << ADSC);
    
    while(ADCSRA & (1 << ADSC));
    
    return ADC;
}