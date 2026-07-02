#include "twi.h"

#include <avr/io.h>
#include <util/twi.h>

#include "config.h"

void twi_init(void)
{
    TWSR = 0x00;
    TWBR = (uint8_t)(((F_CPU / TWI_FREQUENCY_HZ) - 16UL) / 2UL);
    TWCR = (1 << TWEN);
}

uint8_t twi_start(uint8_t address_with_rw)
{
    uint8_t status;

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT))) {
    }

    status = TW_STATUS;
    if ((status != TW_START) && (status != TW_REP_START)) {
        return 0;
    }

    TWDR = address_with_rw;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT))) {
    }

    status = TW_STATUS;
    return (status == TW_MT_SLA_ACK) || (status == TW_MR_SLA_ACK);
}

void twi_stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

uint8_t twi_write(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT))) {
    }

    return TW_STATUS == TW_MT_DATA_ACK;
}

uint8_t twi_read_ack(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT))) {
    }

    return TWDR;
}

uint8_t twi_read_nack(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT))) {
    }

    return TWDR;
}
