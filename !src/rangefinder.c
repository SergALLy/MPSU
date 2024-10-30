#include "..\inc\rangefinder.h"

uint16_t dist=0;

void init_rangefinder()
{
    // Настройка прерываний
    INTERRUPT_RANGEFINDER; // Любое изменение на INT7
    EIMSK |= (1<<ECHO); // Разрешить локально прерывание на INT7
    sei(); // Разрешить прерывание глобально
    // Настройка таймера 1
    RANGEFINDER_SETTING_TIMER;
    // Настройка ног
    DDRE |= (1<<TRIG);
}

ISR(INT7_vect)
{
    // если фронт сигнала на ECHO, то сбрасываем таймер
    if((PINE& (1<<ECHO_PIN)) != 0)
    {
        TCNT1H= 0;
        TCNT1L= 0;
    } 
    else
    { // если срез сигнала на ECHO, то забираем значение
        dist= TCNT1L;
        dist |= (TCNT1H << 8);
    }
}

uint16_t listen_rangefinder()
{
    PORTE |= (1<<TRIG); // Подаем сигнал для начала измерения
    _delay_us(10); 
    PORTE &= ~(1<<TRIG);
    _delay_ms(50); // ждём возаращения сигнала 
/*
    D= t*V/2=t*340/2 м/с = t*0.34/2 мм/мкс = t/2.9/2 мм/мкс = t/5.8  мм/мкс 
    T= 1/(11059200/256) = 1/43200 = 23 мкс
    k = 5.8/23 = 0.25
    D= t/k = t/0.25 = 4*t мм
*/
    return(dist*4);
}