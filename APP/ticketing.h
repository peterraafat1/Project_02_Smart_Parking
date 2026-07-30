#ifndef TICKETING_H
#define TICKETING_H

#include "../Service/STD_Types.h"

#define TICKET_MAX 6u

typedef struct {
    uint16_t id;
    uint32_t entrySec;
    uint8_t  slotHint;
    uint8_t  active;
} Ticket_t;

extern Ticket_t g_tickets[TICKET_MAX];
extern uint16_t g_nextTicketId;

void TKT_Init(void);
int8_t TKT_Issue(uint32_t currentSec, uint8_t suggestedSlot);
int8_t TKT_Close(uint16_t id, uint32_t *entryTime);

#endif