#include "comm.h"

#include <avr/io.h>
#include <stdint.h>

#include "config.h"

static comm_mode_t selected_mode;

static void usart_send_char(char value)
{
    while (!(UCSR0A & (1 << UDRE0))) {
    }

    UDR0 = (uint8_t)value;
}

static void usart_send_text(const char *text)
{
    while (*text) {
        usart_send_char(*text);
        text++;
    }
}

static void usart_send_uint16(uint16_t value)
{
    char buffer[6];
    uint8_t index = 0;

    if (value == 0) {
        usart_send_char('0');
        return;
    }

    while (value > 0 && index < sizeof(buffer)) {
        buffer[index++] = (char)('0' + (value % 10));
        value /= 10;
    }

    while (index > 0) {
        usart_send_char(buffer[--index]);
    }
}

void comm_init(comm_mode_t mode)
{
    uint16_t ubrr = (uint16_t)((F_CPU / (16UL * COMM_BAUD_RATE)) - 1UL);

    selected_mode = mode;

    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void comm_send_record(const log_record_t *record)
{
    if (selected_mode == COMM_MODE_WIRELESS) {
        /* Stub: por enquanto o modo sem fio reutiliza a saida serial. */
    }

    usart_send_text("TEMP=");
    usart_send_uint16(record->sensors.temperature_filtered);
    usart_send_text(";LIGHT=");
    usart_send_uint16(record->sensors.light_filtered);
    usart_send_text(";HUM=");
    usart_send_uint16(record->sensors.humidity_state);
    usart_send_text(";RAIN=");
    usart_send_uint16(record->sensors.rain_state);
    usart_send_text("\r\n");
}
