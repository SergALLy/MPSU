#include <avr/interrupt.h>
#include <util/delay.h>
#include "../INC/sem_ind.h"
#include "../INC/encoder.h"

int16_t angle=0;

int main ()
{   
    int16_t angle_s=0;
    init_sem_ind();
    init_encoder();
    while (1)
    {
        angle_s=angle*9;
        show(angle_s);
    }
}