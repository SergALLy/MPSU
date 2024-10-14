#include "inc/common.h"

uint16_t angle=MIN_POS;

int main()
{
    init_ADC(1,ADEN); // Инициализация АЦП
    init_encoder(); // Инициализация энкодер
    servo_init(); // Инициализация Сервоприводов 1 и 2
    
    uint16_t value=MIN_POS;

    while(1)
    {
        // Чтение значение с 3 канала АЦП
        value = 1.35*read_adc_10(3)+MIN_POS;
        // Ограничение значений угла
        if (angle<MIN_POS) angle=MIN_POS;
        if (angle>MAX_POS) angle=MAX_POS;
        if (value<MIN_POS) value=MIN_POS;
        if (value>MAX_POS) value=MAX_POS;
        // Поворот сервоприводов 1 и 2
        round_1(angle);
        round_2(value);
    }
}