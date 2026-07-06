#include "comm.h"

#include <stdint.h>

#include "config.h"
#include "usart.h"

static comm_mode_t selected_mode;

static void comm_send_timestamp(const log_record_t *record)
{
    usart_send_uint16(record->timestamp.year);
    usart_send_char('-');
    usart_send_uint8_2digits(record->timestamp.month);
    usart_send_char('-');
    usart_send_uint8_2digits(record->timestamp.day);
    usart_send_char('T');
    usart_send_uint8_2digits(record->timestamp.hour);
    usart_send_char(':');
    usart_send_uint8_2digits(record->timestamp.minute);
    usart_send_char(':');
    usart_send_uint8_2digits(record->timestamp.second);
}

void comm_init(comm_mode_t mode)
{
    selected_mode = mode;
    usart_init(COMM_BAUD_RATE);
}

void comm_send_header(void)
{
    usart_send_text("timestamp,temp_raw,temp_filt,light_raw,light_filt,humidity,rain,mode\r\n");
}

void comm_send_record(const log_record_t *record)
{
    if (selected_mode == COMM_MODE_WIRELESS) {
        /* Ainda nao temos o modulo sem fio real; por enquanto sai no mesmo formato serial. */
    }

    /* Linha CSV simples para facilitar leitura no terminal ou planilha. */
    comm_send_timestamp(record);
    usart_send_char(',');
    usart_send_uint16(record->sensors.temperature_raw);
    usart_send_char(',');
    usart_send_uint16(record->sensors.temperature_filtered);
    usart_send_char(',');
    usart_send_uint16(record->sensors.light_raw);
    usart_send_char(',');
    usart_send_uint16(record->sensors.light_filtered);
    usart_send_char(',');
    usart_send_uint16(record->sensors.humidity_state);
    usart_send_char(',');
    usart_send_uint16(record->sensors.rain_state);
    usart_send_char(',');
    usart_send_text(selected_mode == COMM_MODE_USART ? "USART" : "WIRELESS");
    usart_send_text("\r\n");
}
