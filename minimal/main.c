#include <unistd.h>
#include <stdlib.h>
#include "leds.h"
#include "ff.h"

FATFS fs;
char buffer[16];

int main(void)
{
    // default to flash on once
    int flash = 2;
    int i;
    FIL f;

    f_mount(0, &fs);

    // open a new file for writing
    if(f_open(&f, "bootcode", FA_WRITE|FA_OPEN_ALWAYS) == FR_OK)
    {
        // flash twice
        flash = 4;
        // write a number to the file (no newline needed in this case)
        f_puts((const TCHAR *)"12", &f);
        f_close(&f);
    }

    // open the new file for reading
    if(f_open(&f, "bootcode", FA_READ) == FR_OK)
    {
        // flash three times
        flash = 6;

        if(f_gets((TCHAR *)buffer, sizeof(buffer)-1, &f))
        {
            // flash the number of times set in the file
            // decode the number in the file
            flash = atoi(buffer);
        }
        f_close(&f);
    }

    while(1)
    {
        sleep(3);

        for(i = 0; i < flash; i++)
        {
            usleep(250000);
            toggle_led(LED1);
        }
    }

    return 0;
}
