#include "inc/common.h"

int main()
{
    uint16_t value=0; // Значение с АЦП

    init_ADC(1,ADEN); // Настройка и инициализация АЦП
    init_rgb_led(); // Инициализация RGB-диода

    while(1)
    {
        value = read_adc_10(3); // Прочитать значение с АЦП
        color_rgb_led(1023-value, value,0); // Изменение цвета
        _delay_ms(1);
    }
}