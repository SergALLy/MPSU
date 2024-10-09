#ifndef __ADC_H__
#define __ADC_H__

#include "common.h"

void init_ADC(uint8_t num, uint8_t arg, ...);
uint16_t read_adc_10(uint8_t channel);
uint8_t read_adc_8_H(uint8_t channel);

#endif