#include "../inc/servo.h"

void init_servo()
{
    DDRB = (1<<5) | (1<<6);
    // настройка таймера
    SETTING_A_SERVO;
    SETTING_B_SERVO;
    // Настройка периода таймера
    ICR1 = ICR_VAL;
}

void servo_1_turn(uint16_t *angle_servo)
{
    if (*angle_servo<MIN_POS) *angle_servo=MIN_POS;
    if (*angle_servo>MAX_POS) *angle_servo=MAX_POS;
    OCR1A = *angle_servo;
}

void servo_2_turn(uint16_t *angle_servo)
{
    if (*angle_servo<MIN_POS) *angle_servo=MIN_POS;
    if (*angle_servo>MAX_POS) *angle_servo=MAX_POS;
    OCR1B = *angle_servo;
}

uint16_t convert(uint16_t convert_number)
{
    float koef = (MAX_POS-MIN_POS)/1024;
    return (koef*convert_number+MIN_POS);
}