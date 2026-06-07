#include "config.h"

#include <util/delay.h>

#include "datalogger.h"

int main(void)
{
    datalogger_init();

    while (1) {
        datalogger_run_once();
        _delay_ms(LOGGER_SAMPLE_DELAY_MS);
    }
}
