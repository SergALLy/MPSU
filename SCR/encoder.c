#include "../INC/encoder.h"

void init_encoder ()
{
    EICRA |= SETTINGS;
    EIMSK |= (1<<INT0) | (1<<INT2); // Разрешить прерывание от INT0 и INT2
    sei();// разрешить глобально прерывание
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