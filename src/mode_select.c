#include "mode_select.h"

#include <avr/io.h>

#include "config.h"

void mode_select_init(void)
{
    COMM_MODE_SELECT_PIN_DDR &= ~(1 << COMM_MODE_SELECT_PIN);
    COMM_MODE_SELECT_OUT_PORT |= (1 << COMM_MODE_SELECT_PIN);
}

comm_mode_t mode_select_get_comm_mode(void)
{
    if (COMM_MODE_SELECT_PIN_PORT & (1 << COMM_MODE_SELECT_PIN)) {
        return COMM_MODE_USART;
    }

    return COMM_MODE_WIRELESS;
}
