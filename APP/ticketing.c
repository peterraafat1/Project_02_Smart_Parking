#include "ticketing.h"

Ticket_t g_tickets[TICKET_MAX];
uint16_t g_nextTicketId = 1;

void TKT_Init(void) {
    for (uint8_t i = 0; i < TICKET_MAX; i++) {
        g_tickets[i].active = 0;
    }
}

int8_t TKT_Issue(uint32_t currentSec, uint8_t suggestedSlot) {
    for (uint8_t i = 0; i < TICKET_MAX; i++) {
        if (g_tickets[i].active == 0) {
            g_tickets[i].id = g_nextTicketId;
            g_tickets[i].entrySec = currentSec;
            g_tickets[i].slotHint = suggestedSlot;
            g_tickets[i].active = 1;

            g_nextTicketId++;
            if (g_nextTicketId > 9999) {
                g_nextTicketId = 1;
            }
            return i;
        }
    }
    return -1;
}

int8_t TKT_Close(uint16_t id, uint32_t *entryTime) {
    for (uint8_t i = 0; i < TICKET_MAX; i++) {
        if (g_tickets[i].active == 1 && g_tickets[i].id == id) {
            *entryTime = g_tickets[i].entrySec;
            g_tickets[i].active = 0;
            return 0;
        }
    }
    return -1;
}