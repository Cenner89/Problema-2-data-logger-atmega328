#include "rtc.h"

void rtc_init(void)
{
    /* Stub inicial. O driver real sera implementado apos definirmos o modulo RTC. */
}

void rtc_get_time(rtc_time_t *time)
{
    time->second = 0;
    time->minute = 0;
    time->hour = 0;
    time->day = 1;
    time->month = 1;
    time->year = 2026;
}
