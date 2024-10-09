#include "inc/common.h"

uint16_t angle=MIN_POS;

int main()
{
    init_ADC(1,ADEN);
    init_encoder();
    init_servo();
    
    uint16_t value=MIN_POS;

    while(1)
    {
        value = 1.35*read_adc_10(3)+MIN_POS;
        if (angle<MIN_POS) angle=MIN_POS;
        if (angle>MAX_POS) angle=MAX_POS;
        if (value<MIN_POS) value=MIN_POS;
        if (value>MAX_POS) value=MAX_POS;
        servo_1_turn(angle*10);
        servo_2_turn(convert(value));
    }
}