#include "../inc/adc.h"

void init_ADC(uint8_t num, uint8_t arg, ...)
{
    ADCSRA = 0;
    uint8_t *p = &arg;
    while (num--)
    {
        ADCSRA |= (1<<*p);
        p++;
    }
}

uint16_t read_adc_10(uint8_t channel)
{
    // AVCC + выбор канала
    ADMUX = (1 << REFS0) | channel;
    ADCSRA |= (1 << ADSC); // Начало преобразования
    // Ждем окончания преобразования АЦП
    while (!(ADCSRA & (1 << ADIF)))
        ;
    // Сброс флага завершения преобразования
    ADCSRA |= (1 << ADIF);
    uint16_t my_acp =ADCL| (ADCH<<8);
    return (my_acp); // возвращаем результат преобразования
}

uint8_t read_adc_8_H(uint8_t channel)
{
    // AVCC + левое выравнивание + выбор канала
    ADMUX = (1 << REFS0)| (1<<ADLAR) | channel;
    ADCSRA |= (1 << ADSC); // Начало преобразования
    // Ждем окончания преобразования АЦП
    while (!(ADCSRA & (1 << ADIF)))
        ;
    // Сброс флага завершения преобразования
    ADCSRA |= (1 << ADIF);    
    return (ADCH); // возвращаем старшие 8 бит результата
}