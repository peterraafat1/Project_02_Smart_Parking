#include "../Service/STD_Types.h"

#if defined(__has_include)
  #if __has_include(<avr/io.h>)
    #include <avr/io.h>
  #else
    /* Fallback definitions when AVR headers are unavailable */
    #define TCCR1A (*((volatile uint8_t*)0x80))
    #define TCCR1B (*((volatile uint8_t*)0x81))
    #define ICR1   (*((volatile uint16_t*)0x86))
    #define OCR1A  (*((volatile uint16_t*)0x88))
    #define OCR1B  (*((volatile uint16_t*)0x8A))
    #define DDRD   (*((volatile uint8_t*)0x2A))
    #define PD4    4
    #define PD5    5
    #define COM1A1 7
    #define COM1B1 5
    #define WGM11  1
    #define WGM13  4
    #define WGM12  3
    #define CS11   1
  #endif
#else
  #include <avr/io.h>
#endif

#define SERVO_CLOSED_US 1000  
#define SERVO_OPEN_US   2000  

void PWM_Timer1_Init(void) {
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
    
    ICR1 = 19999;
    
    OCR1A = SERVO_CLOSED_US;
    OCR1B = SERVO_CLOSED_US;
    
    DDRD |= (1 << PD4) | (1 << PD5);
}

void BAR_Open(uint8_t ch) {
    if (ch == 1) OCR1A = SERVO_OPEN_US;      
    else if (ch == 2) OCR1B = SERVO_OPEN_US; 
}

void BAR_Close(uint8_t ch) {
    if (ch == 1) OCR1A = SERVO_CLOSED_US;      
    else if (ch == 2) OCR1B = SERVO_CLOSED_US; 
}