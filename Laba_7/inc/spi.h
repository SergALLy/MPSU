#ifndef __SPI_H__
#define __SPI_H__

#include "common.h"

#define CS 2
#define MOSI 3
#define SCK 5

void init_spi(void);
void showMe(int16_t spiData);

#endif