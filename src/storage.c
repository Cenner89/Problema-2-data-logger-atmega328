#include "storage.h"

#include <avr/eeprom.h>

#include "config.h"

#define STORAGE_MAGIC 0xD17AU

static uint16_t EEMEM eeprom_magic;
static uint8_t EEMEM eeprom_write_index;
static log_record_t EEMEM eeprom_records[STORAGE_MAX_RECORDS];

void storage_init(void)
{
    uint16_t magic = eeprom_read_word(&eeprom_magic);

    /* Primeira inicializacao da EEPROM usada pelo projeto. */
    if (magic != STORAGE_MAGIC) {
        eeprom_update_word(&eeprom_magic, STORAGE_MAGIC);
        eeprom_update_byte(&eeprom_write_index, 0);
    }
}

uint8_t storage_save_record(const log_record_t *record)
{
    uint8_t index = eeprom_read_byte(&eeprom_write_index);

    if (index >= STORAGE_MAX_RECORDS) {
        index = 0;
    }

    /* Buffer circular: quando chega no fim, volta e sobrescreve os mais antigos. */
    eeprom_update_block(record, &eeprom_records[index], sizeof(log_record_t));

    index++;
    if (index >= STORAGE_MAX_RECORDS) {
        index = 0;
    }

    eeprom_update_byte(&eeprom_write_index, index);
    return index;
}
