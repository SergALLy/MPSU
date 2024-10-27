#include "inc/common.h"

uint16_t angle=0;

int main()
{
    init_ADC(1,ADEN); // Инициализация АЦП
    init_encoder(); // Инициализация энкодер
    init_servo(); // Инициализация Сервоприводов 1 и 2
    
    uint16_t value=MIN_POS; // Значение с АЦП

    while(1)
    {
 // Преобразуем значение АЦП с учётом масштаба и диапазона
        value = convert(read_adc_10(3)); 
        uint16_t a=angle*10+MIN_POS; // Значение с энкодера
        servo_1_turn(&a); // Управлением 1 сервоприводом
        servo_2_turn(&value); // Управление 2 сервоприводом
    }
}