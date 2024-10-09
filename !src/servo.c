#include "../inc/servo.h"

void servo_init()
{
    DDRB = (1<<5) | (1<<6);
    //быстрая ШИМ, предел счёта: ICR, предделитель: 8
    TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11);
    TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11);
    ICR1 = ICR_VAL;
}

void round_1(uint16_t angle_servo)
{
    OCR1A = angle_servo;
}

void round_2(uint16_t angle_servo)
{
    OCR1B = angle_servo;
}
