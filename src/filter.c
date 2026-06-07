#include "filter.h"
#include "config.h"

void filter_init(lowpass_filter_t *filter)
{
    filter->value = 0;
    filter->initialized = 0;
}

uint16_t filter_update(lowpass_filter_t *filter, uint16_t sample)
{
    int16_t delta;

    if (!filter->initialized) {
        filter->value = sample;
        filter->initialized = 1;
        return filter->value;
    }

    delta = (int16_t)sample - (int16_t)filter->value;
    filter->value = (uint16_t)((int16_t)filter->value + (delta >> FILTER_SHIFT));

    return filter->value;
}
