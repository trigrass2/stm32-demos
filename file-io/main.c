
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
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

void test_task(void* ctx);
void init_devices(void* ctx);

#define  init_devices_task(appdata) xTaskCreate(init_devices,\
                                         "init devices", \
                                         configMINIMAL_STACK_SIZE + 256, \
                                         appdata, \
                                         tskIDLE_PRIORITY + 1, \
                                         NULL)

#define  start_app_task(appdata) xTaskCreate(test_task,\
                                       "test task",\
                                       configMINIMAL_STACK_SIZE + 256, \
                                       appdata,\
                                       tskIDLE_PRIORITY + 1, \
                                       NULL)


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
 * devices must be initialised before the application can make use of them...
 */
void init_devices(void* ctx)
{
    appdata_t* appdata = (appdata_t*)ctx;

    log_init(&appdata->log, "main");

    // initialise filesystem
    sdfs_init();
    log_info(&appdata->log, "wait for filesystem...");
    while(!sdfs_ready());

    // initialize the test usart device
    log_info(&appdata->log, "init %s on %s...", TEST_USART_DEV, "TEST_USART");
    usart_init(TEST_USART, TEST_USART_DEV, false);

    // start up the application
    start_app_task(appdata);

    vTaskDelete(NULL);
}

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

    // create task to initialise hardware devices
    init_devices_task(&appdata);

    // start up the scheduler
    vTaskStartScheduler();

    // should never get here
    return 0;
}
