#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>

#include "types.h"

void storage_init(void);
uint8_t storage_save_record(const log_record_t *record);

#endif
