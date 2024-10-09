#include "../inc/rgb_led.h"

void init_rgb_led() // Инициализация RGB-светодиода и таймера
{
    // Инициализацияпортовввода/вывода
    DDRE = (1<<3) | (1<<4) | (1<<5);
    // Настройка таймера номер 3
    TCCR3A = SETTING_A;
    TCCR3B = SETTING_B;
    // Установка сравниваемого значения
    OCR3AH = 0;
    OCR3AL = 0;
    OCR3BH = 0;
    OCR3BL = 0;
    OCR3CH = 0;
    OCR3CL = 0;
}

void color_rgb_led(uint16_t red, uint16_t green, uint16_t blue) // Изменение регистра OCR3NL 
{
        // Установка яркости каждого из цветов
        OCR3AH = blue>>8; // Синий
        OCR3AL = blue; // Синий
        OCR3AH = green>>8; // Зелёный
        OCR3BL = green; // Зелёный
        OCR3AH = red>>8; // Красный
        OCR3CL = red; // Красный
}