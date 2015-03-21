
#include <math.h>
#include <unistd.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "leds.h"
#include "dac_stream.h"

/**
 * sine wave generator
 */
void dac_stream_callback(uint16_t* buffer, uint16_t length, uint8_t channels, stream_connection_t* conn)
{
    printf("%s: %x %d %d %d\n", conn->name, buffer, length, channels, conn->stream_channel);

    double scale = stream_get_resolution(conn) / 2;
    double offset = stream_get_resolution(conn) / 2;

    // example signal processing - populate the buffer with a sine waveform.
    for(uint16_t i = 0; i < length; i++)
    {
        *buffer = (uint16_t)((scale * sin((i * 2*3.1415) / length)) + offset);
        buffer += channels;
    }
}


stream_connection_t dac_stream_connl;
stream_connection_t dac_stream_connr;

void test_task(void*p)
{
    (void)p;

    dac_stream_init();
    dac_stream_set_samplerate(2000);
    dac_stream_start();
    stream_connection_init(&dac_stream_connl, dac_stream_callback, "dac process l", NULL);
    stream_connection_init(&dac_stream_connr, dac_stream_callback, "dac process r", NULL);
    dac_stream_connect_service(&dac_stream_connl, 0);
    dac_stream_connect_service(&dac_stream_connr, 1);

    for(;;)
    {
        toggle_led(LED2);
        stream_connection_enable(&dac_stream_connl, true);
        stream_connection_enable(&dac_stream_connr, true);

        // wait for a bit - note the callback printf on the console...
        // there will be a sine wave generated on the
        sleep(5);

        stream_connection_enable(&dac_stream_connl, false);
        stream_connection_enable(&dac_stream_connr, false);

        // wait for a bit - note the lack of action on the console...
        sleep(5);
    }
}

#define  start_test_task() xTaskCreate(test_task,\
                                        "test task",\
                                        configMINIMAL_STACK_SIZE + 192, \
                                        NULL,\
                                        tskIDLE_PRIORITY + 3, \
                                        NULL)

int main(void)
{
    // use the system led flasher to flash one of the leds
    flash_led(LED1);
    // use a custom task to flash another led
    start_test_task();
    // start up the scheduler
    vTaskStartScheduler();
    // should never get here
    return 0;
}
