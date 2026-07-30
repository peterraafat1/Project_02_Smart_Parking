#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "STD_Types.h"

#define RING_SIZE 32

typedef struct {
    uint8_t buffer[RING_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
} RingBuffer_t;

void RING_Init(RingBuffer_t *ring);
int8_t RING_Put(RingBuffer_t *ring, uint8_t data);
int8_t RING_Get(RingBuffer_t *ring, uint8_t *data);

#endif