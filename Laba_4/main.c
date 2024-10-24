#include "inc/common.h"

uint16_t angle=0;

int main()
{
    init_ADC(1,ADEN);
    init_encoder();
    init_servo();
    
    uint16_t value=MIN_POS;

    while(1)
    {
        value = convert(read_adc_10(3));
        uint16_t a=angle*10+MIN_POS;
        servo_1_turn(&a);
        servo_2_turn(&value);
    }
}