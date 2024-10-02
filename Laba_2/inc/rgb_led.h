#ifndef __RGB_LED_H__
#define __RGB_LED_H__

//INCLUDE
#include "common.h"
//-------------------------------------------------------

//DEFINE
    /*Инициализация таймера No3. 8-ми
    битная быстрая ШИМ, преддедитель на 8
    сброс OCx3 при совпадении*/
#define SETTING_A (1<<COM3A1)|(1<<COM3B1)|(1<<COM3C1)|(1<<WGM30)
#define SETTING_B (1<<WGM32)|(1<<CS31)
//-------------------------------------------------------

//FUNCTION
void init_rgb_led(); // Инициализация RGB-светодиода и таймера
void color_rgb_led(uint8_t red, uint8_t green, uint8_t blue); // Изменение регистра OCR3NL 
//-------------------------------------------------------

#endif