#ifndef COMM_H
#define COMM_H

#include "types.h"

typedef enum {
    COMM_MODE_USART = 0,
    COMM_MODE_WIRELESS = 1
} comm_mode_t;

void comm_init(comm_mode_t mode);
void comm_send_record(const log_record_t *record);

#endif
