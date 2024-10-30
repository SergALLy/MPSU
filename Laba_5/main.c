#include "inc/common.h"

int main()
{
    uint16_t res = 0;
    uint8_t error[] = {0x79, 0x50, 0x50, 0x5C, 0x50};

    init_sem_ind();     // Инициализация семисегментных индикаторов
    init_rgb_led();     // Инициализация RGB-диода
    init_rangefinder(); // Инициализация дальномера

    while (1)
    {
        res = listen_rangefinder() / 10; // Чтение расстояния в мм
        if (res < 10 || res > 100)
        {
            for (uint8_t i = 0; i < 5; i++) // Вывод на индикаторы "Error"
            {
                PORTA |= (1 << (i + 1));  // Открываем i+1 защёлку
                PORTC = error[i];         // Вывод на i+1 индикатор i букву
                _delay_ms(1);             // Задержка 1мс
                PORTA &= ~(1 << (i + 1)); // Закрываеи i+1 защёлку
            }
            color_rgb_led(1023, 0, 0); // Красный цвет на светодиоде
        }
        else
        {
            sem_ind_show(res); // Вывод в сантиментрах
            color_rgb_led(1023 - res * 10.23, 1023, 1023 - res * 10.23);
        }
    }
}