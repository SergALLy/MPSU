#ifndef __RANGEFINDER_H__
#define __RANGEFINDER_H__

//INCLUDE
#include "common.h"
//-------------------------------------------------------

//DEFINE
#define TRIG 6
#define ECHO_PIN 7
#define ECHO INT7
// Настройка прерываний
#define INTERRUPT_RANGEFINDER EICRB |= (1<<ISC70); // Любое изменение на INT7
/*
    Нормальный, OCR1N отключён, предделитель на 256
    Инициализация таймера No1.
    Нормальный режим, OCR1N отключён,
    преддедитель на 256
*/
#define RANGEFINDER_SETTING_TIMER TCCR1B = (1<<CS12)

//-------------------------------------------------------

//FUNCTION
void init_rangefinder();
uint16_t listen_rangefinder();
//-------------------------------------------------------
#endif