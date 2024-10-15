#include "inc/common.h"

#define TRIG 7

uint16_t dist=0;

init_rangefinder()
{
    // Настройка прерываний
    cli();
    EICRB |= (1<<ISC70); // Любое изменение на INT7
    EIMSK |= (1<<INT7); // Разрешить локально прерывание на INT7
    sei(); // Разрешить прерывание глобально
    // Настройка таймера 1
    TCCR1B = (1<<CS12); // Нормальный, OCR1N отключён, предделитель на 256
    // Настройка ног
    DDRE |= (1<<TRIG);
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
    { // если срез сигнала на ECHO, то забираем значение
        dist= TCNT1L;
        dist |= (TCNT1H << 8);
    }
}

uint16_t listen_rangefinder ()
{
    PORTE |= (1<<TRIG);
    _delay_us(10); // Либо от 15 до 25 мкс 
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

int main ()
{
    uint16_t res=0;

    init_sem_ind();
    init_rgb_led();
    init_rangefinder();

    while(1)
    {
        res = listen_rangefinder()/10;
        if (res<10 && res>100) 
        {
            sem_ind_show(-1);
            color_rgb_led(1023,0,0);
        }
        else
        {
            sem_ind_show(res); // Вывод в сантиментрах
            color_rgb_led(1023-res*10.24,1023,1023-res*10.24);
        }
    }
}