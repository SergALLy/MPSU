#include "../INC/sem_ind.h"

void init_sem_ind ()
{
    DDRA |= 0x3E;
    DDRC = 0x7F;
}

uint8_t digit (int16_t d, int8_t m) 
{
//[]-------------------------------------------------[]
//| Назначение: выделение цифр из разрядов пятиразрядного|
//| десятичного положительного числа |
//| Входные параметры: |
//| d - целое десятичное положительное число |
//| m - номер разряда (от 1 до 5, слева направо) |
//| Возвращается значение цифры в разряде m числа d |
//[]-------------------------------------------------[]
    uint8_t i = 5, a;
    while(i) { // цикл по разрядам числа
        a = d%10; // выделяем очередной разряд
        if(i-- == m) break; // выделен заданный разряд - уходим
        d /= 10; // уменьшаем число в 10 раз
    }
    return(a);
}

uint8_t null_delete (int16_t d)
{
    uint16_t a=10000;
    uint8_t i=1;
    while (d/a == 0)
    {
        i++;
        a/=10;
    }
    return (i);
}

void show (int16_t number)
{
    uint8_t znach_digit=null_delete(abs(number));
    for (uint8_t i=1; i<6; i++)
    {
        PORTA |= (1<<i);
        if (i<znach_digit) PORTC=0;
        else 
        {
            if (number<0)
            {
                PORTA |= (1<<znach_digit-1);
                PORTC = 0x40;
                _delay_ms(1);
                PORTA &= ~(1<<znach_digit-1);
            }
            PORTC = segments[digit(abs(number), i)];
        }
         _delay_ms(1);
        PORTA &= ~(1<<i);
    }
}