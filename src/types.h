#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef struct {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
} rtc_time_t;

typedef struct {
    uint16_t temperature_raw;
    uint16_t light_raw;
    uint16_t temperature_filtered;
    uint16_t light_filtered;
    uint8_t humidity_state;
    uint8_t rain_state;
} sensor_sample_t;

typedef struct {
    rtc_time_t timestamp;
    sensor_sample_t sensors;
} log_record_t;

#endif
