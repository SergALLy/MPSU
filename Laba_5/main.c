#include "inc/common.h"

uint16_t dist=0;

init_rangefinder()
{
    cli();
    EICRB |= (1<<ISC70); // Любое изменение на INT7
    EIMSK |= (1<<INT7); // Разрешить локально прерывание на INT7
    sei(); // Разрешить прерывание глобально
}

ISR(INT7_vect)
{
    // если фронт сигнала на ECHO, то сбрасываем таймер
    if((PINE& (1<<7)) != 0)
    {
        TCNT1H= 0;
        TCNT1L= 0;
    } 
    else
    { //если срез сигнала на ECHO, то забираем значение
        dist= TCNT1L;
        dist |= (TCNT1H << 8);
    }
}

int main ()
{
    
    init_sem_ind();
    init_rgb_led();

    while(1)
    {

    }
}