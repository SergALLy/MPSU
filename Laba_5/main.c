#include "inc/common.h"

int main ()
{
    uint16_t res=0;
    uint8_t error[]={0x79, 0x50, 0x5C};
    init_sem_ind();
    init_rgb_led();
    init_rangefinder();

    while(1)
    {
        res = listen_rangefinder()/10;
        if (res<10 || res>100) 
        {
            //  Вывод на индикаторы "Error"
            PORTA |= (1<<1); // Открываем 1 защёлку
            PORTC = error[0]; // Вывод на 1 индикатор букву "E"
            _delay_ms(1); // Задержка 1мс
            PORTA &= ~(1<<1); // Закрываеи 1 защёлку
            PORTA |= (1<<2); 
            PORTC = error[1]; 
            _delay_ms(1); 
            PORTA &= ~(1<<2); 
            PORTA |= (1<<3); 
            PORTC = error[1]; 
            _delay_ms(1); 
            PORTA &= ~(1<<3); 
            PORTA |= (1<<4); 
            PORTC = error[2]; 
            _delay_ms(1); 
            PORTA &= ~(1<<4); 
            PORTA |= (1<<5); 
            PORTC = error[1]; 
            _delay_ms(1); 
            PORTA &= ~(1<<5); 
            
            color_rgb_led(1023,0,0);
        }
        else
        {
            sem_ind_show(res); // Вывод в сантиментрах
            color_rgb_led(1023-res*10.23,1023,1023-res*10.23);
        }
    }
}