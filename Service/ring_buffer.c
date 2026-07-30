#include "ring_buffer.h"

void RING_Init(RingBuffer_t *ring) {
    ring->head = 0;
    ring->tail = 0;
    ring->count = 0;
}

int8_t RING_Put(RingBuffer_t *ring, uint8_t data) {
    if (ring->count >= RING_SIZE) {
        return -1;
    }
    ring->buffer[ring->head] = data;
    ring->head = (ring->head + 1) % RING_SIZE;
    ring->count++;
    return 0;
}

int8_t RING_Get(RingBuffer_t *ring, uint8_t *data) {
    if (ring->count == 0) {
        return -1;
    }
    *data = ring->buffer[ring->tail];
    ring->tail = (ring->tail + 1) % RING_SIZE;
    ring->count--;
    return 0;
}