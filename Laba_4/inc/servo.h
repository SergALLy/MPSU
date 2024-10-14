#ifndef __SERVO_H__
#define __SERVO_H__
#include "common.h"

#define ICR_VAL 27648 // 11059200/8/50=27648
#define MIN_POS (ICR_VAL/20)
#define MAX_POS (ICR_VAL/10)
#define SETTING_A_SERVO TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11)
#define SETTING_B_SERVO TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11)

void servo_init();
void round_1(uint16_t angle_servo);
void round_2(uint16_t angle_servo);

#endif