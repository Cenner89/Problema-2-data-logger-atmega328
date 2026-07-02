#include "usart.h"

#include <avr/io.h>

#include "config.h"

void usart_init(uint32_t baud_rate)
{
    uint16_t ubrr = (uint16_t)((F_CPU / (16UL * baud_rate)) - 1UL);

    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void usart_send_char(char value)
{
    while (!(UCSR0A & (1 << UDRE0))) {
    }

    UDR0 = (uint8_t)value;
}

void usart_send_text(const char *text)
{
    while (*text) {
        usart_send_char(*text);
        text++;
    }
}

void usart_send_uint8_2digits(uint8_t value)
{
    usart_send_char((char)('0' + ((value / 10) % 10)));
    usart_send_char((char)('0' + (value % 10)));
}

void usart_send_uint16(uint16_t value)
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
