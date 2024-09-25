#include <avr/interrupt.h>
#include <util/delay.h>

int16_t angle=0;
const uint8_t segments[] = {0x3F, 0x06, 0x5B, 0x4F,0x66, 0x6D,0x7D, 0x07, 0x7F, 0x6F};

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

ISR(INT0_vect)
{
    if((PIND & (1 << 0)) != 0) {
        EICRA = (1<<ISC01) | (1<<ISC21);
        if((PIND & (1 << 1)) != 0) angle++;
        else angle--;
    }
    else {
        EICRA = (1 << ISC01) | (1<<ISC00)| (1<<ISC21);
        if((PIND & (1 << 1)) != 0) angle--;
        else angle++;
    }
}

ISR(INT2_vect)
{
    angle = 0;
}

int main ()
{   
    int16_t angle_s=0;
    DDRA |= 0x3E;
    DDRC = 0x7F;
    EICRA |= (1<<ISC00) | (1<<ISC01) | (1<<ISC21); // Нарастающий фронт на INT0 на INT2
    EIMSK |= (1<<INT0) | (1<<INT2); // Разрешить прерывание от INT0 и INT2
    sei() ;// разрешить глобально прерывание
    while (1)
    {
        angle_s=angle*9;
        uint8_t znach_digit=null_delete(abs(angle_s));
        for (uint8_t i=1; i<6; i++)
        {
            PORTA |= (1<<i);
            if (i<znach_digit) PORTC=0;
            else 
            {
                if (angle_s<0)
                {
                    PORTA |= (1<<znach_digit-1);
                    PORTC = 0x40;
                    _delay_ms(1);
                    PORTA &= ~(1<<znach_digit-1);
                }
                PORTC = segments[digit(abs(angle_s), i)];
            }
            _delay_ms(1);
            PORTA &= ~(1<<i);
        }

    }
};
