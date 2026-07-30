# Smart Parking System Controller

A concurrent smart parking system controller managing a 6-slot car park with independent entry and exit lanes on the AVR ATmega32A microcontroller.

---

## Author

**Peter Raafat Barty Saleh**

---

## Project Overview

This project implements a complete firmware solution for a smart parking lot. The core engineering achievement is achieving **concurrency without an RTOS**. The system manages an entry lane and an exit lane simultaneously using a reusable, non-blocking Finite State Machine (FSM) dispatched from a single 10 ms tick.

The controller handles vehicle detection (ADC), barrier control (Timer1 Fast PWM), occupancy tracking, real-time ticketing (UART), billing calculations, and statistics persistence (SPI EEPROM).

The codebase follows a strict layered architecture (APP, HAL, MCAL, Service) ensuring highly modular, hardware-independent logic.

---

## Features

- **True Concurrency:** Dual-lane FSM allowing simultaneous entry and exit operations without blocking delays.
- **Servo Barrier Control:** Accurate 20 ms frame PWM generation via Timer1 hardware.
- **Smart Ticketing & Billing:** Sequential ID generation, timestamping, and tariff arithmetic (including grace periods and daily caps).
- **Persistent Statistics:** Rolling statistics and configurations saved to SPI EEPROM with write-throttling.
- **Hardware Interfacing:** Multiplexed UI using an I2C 16x2 LCD and a 7-segment display.
- **Robustness:** Passage timeout handling, sensor debounce, and limit fault recovery.

---

## Folder Structure

```text
Project
│
├── APP/
│   ├── lot_fsm.c
│   ├── lane_fsm.c
│   ├── ticketing.c
│   └── billing.c
│
├── HAL/
│   ├── slots.c
│   ├── barrier.c
│   ├── seg7.c
│   ├── lcd_i2c.c
│   └── eeprom_spi.c
│
├── MCAL/
│   ├── DIO/
│   ├── ADC/
│   ├── Timer/
│   ├── USART/
│   ├── SPI/
│   └── I2C/
│
├── Service/
│   ├── STD_Types.h
│   ├── Bit_Math.h
│   ├── ring_buffer.c
│   └── softrtc.c
│
├── src/
│   └── main.c
│
├── build/
├── Makefile
└── README.md