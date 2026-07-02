#ifndef RTC_H
#define RTC_H

#include "types.h"

void rtc_init(void);
uint8_t rtc_get_time(rtc_time_t *time);

#endif
