#include "rtc.h"

#include <stdint.h>

#include "config.h"
#include "twi.h"

static uint8_t bcd_to_decimal(uint8_t value)
{
    return (uint8_t)(((value >> 4) * 10U) + (value & 0x0FU));
}

static void rtc_set_fallback_time(rtc_time_t *time)
{
    time->second = 0;
    time->minute = 0;
    time->hour = 0;
    time->day = 1;
    time->month = 1;
    time->year = RTC_FALLBACK_YEAR;
}

void rtc_init(void)
{
    twi_init();
}

uint8_t rtc_get_time(rtc_time_t *time)
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint8_t year;

    if (!twi_start((RTC_DS3231_ADDRESS << 1) | 0U)) {
        rtc_set_fallback_time(time);
        return 0;
    }

    if (!twi_write(0x00)) {
        twi_stop();
        rtc_set_fallback_time(time);
        return 0;
    }

    if (!twi_start((RTC_DS3231_ADDRESS << 1) | 1U)) {
        twi_stop();
        rtc_set_fallback_time(time);
        return 0;
    }

    second = twi_read_ack();
    minute = twi_read_ack();
    hour = twi_read_ack();
    (void)twi_read_ack(); /* Dia da semana: nao usado nesta etapa. */
    day = twi_read_ack();
    month = twi_read_ack();
    year = twi_read_nack();
    twi_stop();

    time->second = bcd_to_decimal(second & 0x7FU);
    time->minute = bcd_to_decimal(minute & 0x7FU);
    time->hour = bcd_to_decimal(hour & 0x3FU);
    time->day = bcd_to_decimal(day & 0x3FU);
    time->month = bcd_to_decimal(month & 0x1FU);
    time->year = (uint16_t)(2000U + bcd_to_decimal(year));

    return 1;
}
