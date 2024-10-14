#include "inc/common.h"

uint16_t read_adc(uint8_t channel)
{
    // AVCC + правое выравнивание + выбор канала
    ADMUX = (1<<REFS0) | channel;
    ADCSRA|= (1<<ADSC); // Начало преобразования, частота Fcpu
    // Ждем окончания преобразования АЦП
    while(!(ADCSRA & (1<<ADIF)));
    // Сброс флага завершения преобразования
    ADCSRA|= (1<<ADIF);
    return(ADCL|ADCH<<8); // возвращаем результат
}


int main()
{
    uint16_t value=0; // Значение с АЦП

    ADCSRA|= (1<<ADEN); // Включение модуля АЦП

    init_rgb_led(); // Инициализация RGB-диода
    while(1)
    {
        value = read_adc(3); // Прочитать значение с АЦП
        color_rgb_led(1023-value, value,0); // Изменение цвета
        _delay_ms(1); 
    }
}