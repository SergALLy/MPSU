#include "../inc/common.h"

int16_t angle=0; // Значение угла поворота

int main()
{
    // Инициализацияпортовввода/вывода
    DDRE = (1<<3) | (1<<4) | (1<<5);
    /*Инициализациятаймера No3. 8-ми
    битная быстрая ШИМ, преддедитель на 8
    сброс при совпадении*/
    TCCR3A = (1<<COM3A1)|(1<<COM3B1)|(1<<COM3C1)|(1<<WGM30);
    TCCR3B = (1<<WGM32) | (1<<CS31);
    // Установка сравниваемого значения
    OCR3AH = 0;
    OCR3AL = 0;
    OCR3BH = 0;
    OCR3BL = 255;
    OCR3CH = 0;
    OCR3CL = 255;

    init_encoder(); // Инициализация энкодера
    LCD_init(); // Инициализация ЖКИ дисплея

    while(1)
    {
        // Ограничение переменной angle
        if (angle>255) angle=255;
        if (angle<0) angle=0;
        // Установка яркости каждого из цветов
        OCR3AL = 255-angle; // Синий
        OCR3BL = 255-angle; // Зелёный
        OCR3CL = angle; // Красный
        // Вывод на экран
        LCD_vyvod("R: ");
        LCD_number(angle);
        LCD_vyvod(" G: ");
        LCD_number(255-angle);
        LCD_vyvod(" B: ");
        LCD_number(255-angle);
        LCD_data(ADDRES|0); // Передвинуть курсор на 0 место 
        _delay_ms(1);
    }
}