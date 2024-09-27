#ifndef __SEM_IND_H__
#define __SEM_IND_H__
//INCLUDE
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
//-------------------------------------------------------
//DEFINE

//-------------------------------------------------------
//FUNCTION
void init_sem_ind ();
uint8_t digit (int16_t d, int8_t m);
uint8_t null_delete (int16_t d);
void show (int16_t number);
//-------------------------------------------------------
//VAR
const uint8_t segments[] = {0x3F, 0x06, 0x5B, 0x4F,0x66, 0x6D,0x7D, 0x07, 0x7F, 0x6F};
//-------------------------------------------------------
#endif