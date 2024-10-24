#ifndef __RGB_LED_H__
#define __RGB_LED_H__

//INCLUDE
#include "common.h"
//-------------------------------------------------------

//DEFINE
    /*Инициализация таймера No3. 10-ми
    битная быстрая ШИМ, преддедитель на 8
    сброс OC3N при совпадении*/
#define RGB_SETTING_A TCCR3A=(1<<COM3A1)|(1<<COM3B1)|(1<<COM3C1)|(1<<WGM31)|(1<<WGM30)
#define RGB_SETTING_B TCCR3B=(1<<WGM32)|(1<<CS31)
//-------------------------------------------------------

//FUNCTION
void init_rgb_led(); // Инициализация RGB-светодиода и таймера
void color_rgb_led(uint16_t red, uint16_t green, uint16_t blue); // Изменение регистра OCR3NL 
//-------------------------------------------------------

#endif