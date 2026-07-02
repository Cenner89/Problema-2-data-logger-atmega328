#ifndef USART_H
#define USART_H

#include <stdint.h>

void usart_init(uint32_t baud_rate);
void usart_send_char(char value);
void usart_send_text(const char *text);
void usart_send_uint8_2digits(uint8_t value);
void usart_send_uint16(uint16_t value);

#endif
