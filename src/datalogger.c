#include "datalogger.h"

#include "comm.h"
#include "mode_select.h"
#include "rtc.h"
#include "sensors.h"
#include "storage.h"
#include "types.h"

void datalogger_init(void)
{
    /* Inicializacao geral. A ordem aqui foi deixada explicita para ficar facil de acompanhar. */
    sensors_init();
    rtc_init();
    storage_init();
    mode_select_init();
    comm_init(mode_select_get_comm_mode());
    comm_send_header();
}

void datalogger_run_once(void)
{
    log_record_t record;

    /* Ciclo principal do data-logger: pega horario, le sensores, salva e envia. */
    (void)rtc_get_time(&record.timestamp);
    sensors_read(&record.sensors);
    (void)storage_save_record(&record);
    comm_send_record(&record);
}
