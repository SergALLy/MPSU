#ifndef __COMMON_H__
#define __COMMON_H__

// Общие библиотеки
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Пользовательские библиотеки
#include "encoder.h" // Работа с энкодером и кнопкой
#include "sem_ind.h" // Работа с матрицей семисегментных индикаторов
#include "lcd.h" // Работа с ЖКИ
#include "rgb_led.h" // Работа с RGB-светодиодом
#include "adc.h" // Работа с АЦП
#include "servo.h" // Работа с сервоприводами
#include "rangefinder.h" // Работа с ультразвуковым дальномером
#include "twi.h" // Работа матрицей через I2C

#endif