#include "inc/common.h"

int16_t angle=0; // Угол поворота 

int main ()
{   
    int16_t angle_g=0; // Значение угла поворота в градусах
    init_sem_ind(); // Инициализация семисегментного индикатора
    init_encoder(); // Инициализация энкодера
    while (1)
    {
        angle_g=angle*9; // Пересчёт угла поворота в градусы
        show(angle_g); // Вывод значения угла на семисегментном индикаторе
    }
}