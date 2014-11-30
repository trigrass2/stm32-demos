#include <unistd.h>
#include "leds.h"

int main(void)
{
    // default to flash on once
    int i;

    while(1)
    {
        sleep(1);

        for(i = 0; i < 6; i++)
        {
            usleep(100000);
            toggle_led(LED1);
        }
    }

    return 0;
}
