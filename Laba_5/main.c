#include "inc/common.h"

int main ()
{
    uint16_t res=0;

    init_sem_ind();
    init_rgb_led();
    init_rangefinder();

    while(1)
    {
        res = listen_rangefinder()/10;
        if (res<10 && res>100) 
        {
            sem_ind_show(-1);
            color_rgb_led(1023,0,0);
        }
        else
        {
            sem_ind_show(res); // Вывод в сантиментрах
            color_rgb_led(1023-res*10.23,1023,1023-res*10.23);
        }
    }
}