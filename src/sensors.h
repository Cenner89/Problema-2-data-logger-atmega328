#ifndef SENSORS_H
#define SENSORS_H

#include "types.h"

void sensors_init(void);
void sensors_read(sensor_sample_t *sample);

#endif
