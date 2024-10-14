#include "../inc/servo.h"

void servo_init()
{
    DDRB = (1<<5) | (1<<6);
    // настройка таймера
    SETTING_A_SERVO;
    SETTING_B_SERVO;
    // Настройка периода таймера
    ICR1 = ICR_VAL;
}

void round_1(uint16_t angle_servo) // Поворот сервопривода 1
{
    OCR1A = angle_servo;
}

void round_2(uint16_t angle_servo) // Поворот сервопривода 2
{
    OCR1B = angle_servo;
}
