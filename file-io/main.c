
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "leds.h"
#include "usart.h"
#include "sdfs.h"
#include "logger.h"


/**
 * a data structure that holds data used by this application
 *
 * just holds a logger for this project.
 * for a large project loggers are good because they can be turned on and off in software,
 * can pipe log data to various endpoints, and can be compiled out to save space using
 * the option USE_LOGGER=0 in the makefile.
 */
typedef struct {
    logger_t log;
} appdata_t;

/**
 * the test device is to be named /dev/ttyS0, attached to the CONSOLE_USART
 * Note: the CONSOLE_USART transmit is captured by default for use by SDTOUT
 * in this application we will only use CONSOLE_USART receiver
 */
#define TEST_USART_DEV        "/dev/ttyS0"
#define TEST_USART            CONSOLE_USART
#define TEST_USART_MODE        O_RDONLY
#define TEST_USART_BUFSIZE    128
#define TEST_DATAFILE        "datafile.txt"

/**
 * example of an application task
 *
 * this task performs a data logger function, reading data from USART2
 * and logging it to a file.
 */
void test_task(void* ctx)
{
#if USE_LOGGER
    appdata_t* appdata = (appdata_t*)ctx;
#else
    (void)ctx;
#endif
    char buffer[256];
    int ret;
    FILE* datafile;
    int serial;

    log_info(&appdata->log, "starting application");

    // open the uart in read mode only - the console already has the write port open
    // fopen is not supported for devices - use the open system call
    serial = open(TEST_USART_DEV, TEST_USART_MODE, TEST_USART_BUFSIZE);

    // remove old file if there was one
    unlink(TEST_DATAFILE);

#if 0
    for(;;)
    {
        // fopen is the most convenient method of opening a regular file
        datafile = fopen(TEST_DATAFILE, "a");

        if(datafile != NULL)
        {
            // use the read system call for devices
            ret = read(serial, buffer, sizeof(buffer));
            if(ret != EOF && ret > 0)
            {
                buffer[ret] = '\0';
                fputs(buffer, datafile);
                log_info(&appdata->log, "got: %s", buffer);
            }
            else
            {
                log_info(&appdata->log, "file size: %d", ftell(datafile));
                sleep(1);
            }

            toggle_led(LED2);

            fclose(datafile);
        }
        else
        {
            log_info(&appdata->log, "couldnt open %s", TEST_DATAFILE);
            sleep(1);
        }
        taskYIELD();
    }
#else
    // fopen is the most convenient method of opening a regular file
   datafile = fopen(TEST_DATAFILE, "w");

   for(;;)
   {
       if(datafile != NULL)
       {
           // use the read system call for devices
           ret = read(serial, buffer, sizeof(buffer));
           if(ret != EOF && ret > 0)
           {
               buffer[ret] = '\0';
               fputs(buffer, datafile);
               fflush(datafile);
               log_info(&appdata->log, "got: %s", buffer);
           }
           else
           {
               log_info(&appdata->log, "file size: %d", ftell(datafile));
               sleep(1);
           }

           toggle_led(LED2);

       }
       else
       {
           log_info(&appdata->log, "couldnt open %s", TEST_DATAFILE);
           sleep(1);
       }
       taskYIELD();
   }
   fclose(datafile);
#endif

}


int main(void)
{
    // use the system led flasher to flash one of the leds
    flash_led(LED1);

    appdata_t appdata;

    log_init(&appdata.log, "main");

	// initialise filesystem
	sdfs_init();
	log_info(&appdata.log, "wait for filesystem...");
	while(!sdfs_ready());

	// initialize the test usart device
	log_info(&appdata.log, "init %s on %s...", TEST_USART_DEV, "TEST_USART");
	usart_init(TEST_USART, TEST_USART_DEV, false);

	// start up the application
    pthread_t app_thread;
	pthread_attr_t app_attr;
	pthread_attr_init(&app_attr);
	pthread_attr_setstacksize(&app_attr, 384);
	pthread_attr_setdetachstate(&app_attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&app_thread, &app_attr, (void*(*)(void*))test_task, &appdata);
	pthread_attr_destroy(&app_attr);

	pthread_exit(0);
    return 0;
}
