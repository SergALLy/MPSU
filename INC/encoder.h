#ifndef __ENCODER_H__
#define __ENCODER_H__
//INCLUDE
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//-------------------------------------------------------
//DEFINE
#define SETTINGS (1<<ISC00) | (1<<ISC01) | (1<<ISC21) // Нарастающий фронт на INT0 на INT2
//-------------------------------------------------------
//FUNCTION

void init_encoder ();
//-------------------------------------------------------
//VAR
extern int16_t angle;
//-------------------------------------------------------

#endif 