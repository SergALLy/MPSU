#include "inc/common.h"

int main()
{
    uint16_t value=0;

    init_ADC(1,ADEN);
    init_rgb_led();

    while(1)
    {
        value = read_adc_10(3); // Прочитать значение с АЦП
        color_rgb_led(1023-value, value,0);
        _delay_ms(1);
    }
}