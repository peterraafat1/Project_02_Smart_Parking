CC      = avr-gcc
OBJCOPY = avr-objcopy
MCU     = atmega32a
F_CPU   = 8000000UL
CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -std=c99 -Wall -Wextra -Os

C_SOURCES := \
    src/main.c \
    APP/lane_fsm.c \
    APP/ticketing.c \
    APP/billing.c \
    APP/lot_fsm.c \
    HAL/slots.c \
    HAL/eeprom_spi.c \
    HAL/lcd_i2c.c \
    HAL/seg7.c \
    MCAL/adc.c \
    MCAL/pwm.c \
    MCAL/timer.c \
    MCAL/usart.c \
    MCAL/spi.c \
    MCAL/i2c.c \
    MCAL/exti.c \
    MCAL/dio.c \
    Service/ring_buffer.c \
    Service/softrtc.c

OBJS   := $(patsubst %.c,build/%.o,$(C_SOURCES))
TARGET := build/firmware

all: $(TARGET).hex

$(TARGET).elf: $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build

.PHONY: all clean