#include "inc/common.h"

int16_t angle=0; // Значение угла поворота

int main()
{

    init_encoder(); // Инициализация энкодера
    init_rgb_led(); // Инициализация RGB-светодиода
    LCD_init(); // Инициализация ЖКИ дисплея
    LCD_vyvod("R:     G:");
    LCD_cmd(ADDRES|64);
    LCD_vyvod("B: ");
    while(1)
    {
        // Ограничение переменной angle
        if (angle>255) angle=255;
        if (angle<0) angle=0;
        // Установка яркости каждого из цветов
        color_rgb_led(angle, 255-angle, 255-angle);
        // Вывод на экран
        LCD_cmd(ADDRES|3);
        LCD_vyvod("   ");
        LCD_cmd(ADDRES|3);
        LCD_number(angle);

        LCD_cmd(ADDRES|10);
        LCD_vyvod("   ");
        LCD_cmd(ADDRES|10);
        LCD_number(255-angle);

        LCD_cmd(ADDRES|67);
        LCD_vyvod("   ");
        LCD_cmd(ADDRES|67);
        LCD_number(255-angle);

        _delay_us(500);
    }
}