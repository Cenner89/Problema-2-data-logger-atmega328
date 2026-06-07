#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>

typedef struct {
    uint16_t value;
    uint8_t initialized;
} lowpass_filter_t;

void filter_init(lowpass_filter_t *filter);
uint16_t filter_update(lowpass_filter_t *filter, uint16_t sample);

#endif
