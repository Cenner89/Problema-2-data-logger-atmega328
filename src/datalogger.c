#include "datalogger.h"

#include "comm.h"
#include "rtc.h"
#include "sensors.h"
#include "types.h"

void datalogger_init(void)
{
    sensors_init();
    rtc_init();
    comm_init(COMM_MODE_USART);
}

void datalogger_run_once(void)
{
    log_record_t record;

    rtc_get_time(&record.timestamp);
    sensors_read(&record.sensors);
    comm_send_record(&record);
}
