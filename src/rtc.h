#ifndef RTC_H
#define RTC_H

#include "types.h"

void rtc_init(void);
void rtc_get_time(rtc_time_t *time);

#endif
