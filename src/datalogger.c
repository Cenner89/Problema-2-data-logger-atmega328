#include "datalogger.h"

#include "comm.h"
#include "mode_select.h"
#include "rtc.h"
#include "sensors.h"
#include "types.h"

void datalogger_init(void)
{
    sensors_init();
    rtc_init();
    mode_select_init();
    comm_init(mode_select_get_comm_mode());
}

void datalogger_run_once(void)
{
    log_record_t record;

    rtc_get_time(&record.timestamp);
    sensors_read(&record.sensors);
    comm_send_record(&record);
}
