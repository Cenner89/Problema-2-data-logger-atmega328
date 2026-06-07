#include "sensors.h"

#include <avr/io.h>

#include "adc.h"
#include "config.h"
#include "filter.h"

static lowpass_filter_t temperature_filter;
static lowpass_filter_t light_filter;

void sensors_init(void)
{
    adc_init();

    SENSOR_HUMIDITY_PIN_DDR &= ~(1 << SENSOR_HUMIDITY_PIN);
    SENSOR_RAIN_PIN_DDR &= ~(1 << SENSOR_RAIN_PIN);

    filter_init(&temperature_filter);
    filter_init(&light_filter);
}

void sensors_read(sensor_sample_t *sample)
{
    sample->temperature_raw = adc_read(ADC_CHANNEL_TEMPERATURE);
    sample->light_raw = adc_read(ADC_CHANNEL_LIGHT);

    sample->temperature_filtered = filter_update(&temperature_filter, sample->temperature_raw);
    sample->light_filtered = filter_update(&light_filter, sample->light_raw);

    sample->humidity_state = (SENSOR_HUMIDITY_PIN_PORT & (1 << SENSOR_HUMIDITY_PIN)) ? 1 : 0;
    sample->rain_state = (SENSOR_RAIN_PIN_PORT & (1 << SENSOR_RAIN_PIN)) ? 1 : 0;
}
