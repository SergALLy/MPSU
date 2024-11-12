#include "inc/common.h"

int main()
{
    init_spi(); // включить аппаратный SPI, режим 0, предделительна 128
    while (1)
    {
        for (int16_t i = -990; i < 1000; i += 10)
        {
            showMe(i);
            _delay_ms(100);
        }
    }
}