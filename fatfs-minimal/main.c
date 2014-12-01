#include <unistd.h>
#include <stdlib.h>
#include "leds.h"
#include "sdfs.h"

#define TEST_FILENAME   "testfile"
#define TEST_FLASHES   "10"


typedef struct {
    FATFS fs;
    char buffer[16];
    FIL file;
    int flash;
    int count;
}appdata_t;

/**
 * put the struct in bss - in my setup the stack is located in CCRAM on stm32f4 devices.
 * the filesystem uses DMA, which cant be used with CCRAM.
 */
appdata_t appdata = {
    .flash = 1,             // default to flash on once
};

int main(void)
{
    int i;

    if(sdfs_init())
    {
        // open a new file for writing
        if(f_open(&appdata.file, TEST_FILENAME, FA_WRITE|FA_OPEN_ALWAYS) == FR_OK)
        {

            // flash twice
            appdata.flash = 2;
            // write a number to the file (no newline needed in this case)
            f_puts((const TCHAR *)TEST_FLASHES, &appdata.file);
            f_close(&appdata.file);
        }

        // open the new file for reading
        if(f_open(&appdata.file, TEST_FILENAME, FA_READ) == FR_OK)
        {
            // flash three times
            appdata.flash = 3;

            if(f_gets((TCHAR *)appdata.buffer, sizeof(appdata.buffer)-1, &appdata.file))
            {
                // flash the number of times set in the file
                // decode the number in the file
                appdata.flash = atoi(appdata.buffer);
            }
            f_close(&appdata.file);
        }
    }

    while(1)
    {
        for(i = 0; i < appdata.flash; i++)
        {
            set_led(LED1);
            usleep(100000);
            clear_led(LED1);
            usleep(200000);
        }

        sleep(1);
    }

    return 0;
}
