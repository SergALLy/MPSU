#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define _BV(b) (1 << (b))
#define MUX (_BV(REFS0))
#define BIT_IS_CLEAR(Reg, b) ((Reg & _BV(b)) == 0)
uint8_t readAdc(uint8_t channel)
{
    ADMUX = MUX | (1 << ADLAR) | channel;
    //delay_us(10);
    ADCSRA |= _BV(ADSC);
    while (BIT_IS_CLEAR(ADCSRA, ADIF));
    ADCSRA |= _BV(ADIF);
    return ADCH;
}
int main(void)
{
    // Инициализация портов ввода/вывода
    DDRB = _BV(5);
    DDRG = _BV(3);
    // Инициализация АЦП
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) |
             _BV(ADPS0);
    // Инициализация таймера 1. Быстрая ШИМ 8 бит
    TCCR1A = _BV(COM1A1) | _BV(WGM10);
    TCCR1B = _BV(WGM12) | _BV(CS10);
    /* переменные магнитного поля, ошибки регулирования и
    управления (здесь будут ещё переменные, например,
    значение ошибки регулирования на предыдущем шаге)*/
    float field, error = 0, ref, control;
    float derivative=0, last_error=0,integral=0;
    while (1)
    {
        // АЦП 8 бит и предделитель на 128
        ref = (readAdc(3) + readAdc(3) + readAdc(3)) / 3;
        /* здесь (мб) должно быть ограничение задания, чтоб
        шайба не улетала*/
        field = (readAdc(1) + readAdc(1) + readAdc(1)) / 3;
        error = ref / 2 - field;
        derivative = (error - last_error);
        last_error = error;
        integral += error;
        control = error * 5.0 + integral * 0.0035 + derivative *250.0;
        //control = error * 5.0 + integral * 0.003 + derivative *250.0;
        if (control > 255) // ограничение управления сверху
            control = 255;
        if (control < -255) // ограничение управления снизу
            control = -255;
        if (control >= 0)
        { // установка сигнала управления
            PORTG &= ~(1 << 3);
            OCR1AL = (uint8_t)control;
        }
        else
        {
            PORTG |= (1 << 3);
            OCR1AL = (uint8_t)(-control);
        }
    }
}