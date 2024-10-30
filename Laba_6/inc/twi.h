#ifndef __TWI_H__
#define __TWI_H__

#include "common.h"

#define DEV_ADDR 0b1100000 // адрес модуля по умолчанию 
#define W 0 // признак записи данных в матрицу
#define R 1 // признак чтения данных из матрицы 

#define COLUMN_DATA_REG 0x01 // регистр состояния диодов столбца 
#define UPDATE_COLUMN_REG 0x0C // регистр обновления состояния диодов столбца

void matrDrawPict(uint8_t devAddr, uint8_t *dataBuf);
void init_twi(uint8_t devAddr);

#endif