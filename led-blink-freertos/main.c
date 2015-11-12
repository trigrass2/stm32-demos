

#include <unistd.h>
#include <pthread.h>
#include "leds.h"

int main(void)
{
    // use the system led flasher to flash one of the leds
    flash_led(LED1);

    for(;;)
    {
        toggle_led(LED2);
        usleep(250000);
    }

    pthread_exit(0);
    // should never get here
    return 0;
}
