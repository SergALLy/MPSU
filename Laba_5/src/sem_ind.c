#include "../inc/sem_ind.h"

const uint8_t segments[] = {0x3F, 0x06, 0x5B, 0x4F,0x66, 0x6D,0x7D, 0x07, 0x7F, 0x6F}; // Код цифр для семисегментного индикатора

int16_t my_abs (int16_t a) // Поиск модуля
{
    return ((a>=0)? a: -a); // Ессли число a >= 0 возвращаем a, иначе -a 
}

void init_sem_ind () // Инициализация семисегментного индикатора
{
    DDRA |= 0x3E;
    DDRC = 0xFF;
}

uint8_t digit (int16_t d, int8_t m) // Поиск цифры 
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
    while(i) { // Цикл по разрядам числа
        a = d%10; // Выделяем очередной разряд
        if(i-- == m) break; // Выделен заданный разряд - уходим
        d /= 10; // Уменьшаем число в 10 раз
    }
    return(a);
}

uint8_t null_delete (int16_t d) // Поиск значащей цифры
{
//[]-------------------------------------------------[]
//| Назначение: Поиск номера индикатора, с которого |
//| начинается число d |
//| Входные параметры: |
//| d - исходное целое число |
//| Возращает номер индикатора с которого начинается |
//| число d |
//[]-------------------------------------------------[]
    uint16_t a=10000;
    uint8_t i=1; // Номер индикатора
    while (d/a == 0 && i!=5) // Поиск индикатора с первой цифрой
    {
        i++;
        a/=10;
    }
    return (i);
}

void sem_ind_show (int16_t number) // Вывод на семисегментный индикатор числа
{
 //[]-------------------------------------------------[]
//| Назначение: вывод пятизначного десятичного числа |
//| на матрицу семисегментых индикаторов |
//| Входные параметры: |
//| number  - целое десятичное число |
//[]-------------------------------------------------[]   
    uint8_t znach_digit=null_delete(my_abs(number)); // Номер индикатора, с которого начинается число number
    for (uint8_t i=1; i<6; i++) // Проход по каждому семисегментному индикатору
    {
        PORTA |= (1<<i); // Открываем i защёлку
        if (i<znach_digit) PORTC=0; // Провека на наличие цифры
        else 
        {
            if (number<0) // Проверка на отрицательное число
            {
                PORTA |= (1<<(znach_digit-1)); // Открываем i-1 защёлку
                PORTC = 0x40; // Вывод минуса
                _delay_ms(1); // Задержка 1мс
                PORTA &= ~(1<<(znach_digit-1)); // Закрываем i-1 защёлку
            }
            PORTC = segments[digit(my_abs(number), i)]; // Вывод на i индикатор i цифру числа number
        }
         _delay_ms(1); // Задержка 1мс
        PORTA &= ~(1<<i); // Закрываеи i защёлку
    }
}