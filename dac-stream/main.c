
#include <unistd.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "leds.h"
#include "dac_stream.h"


void dac_stream_callback(uint16_t* buffer, uint16_t length, uint8_t channels, stream_connection_t* conn)
{
    printf("%s: %x %d %d %d\n", conn->name, buffer, length, channels, conn->stream_channel);
}

stream_connection_t dac_stream_conn;

void test_task(void*p)
{
    (void)p;

    dac_stream_init();
    dac_stream_set_samplerate(2000);
    dac_stream_start();
    stream_connection_init(&dac_stream_conn, dac_stream_callback, "dac process", NULL);
    dac_stream_connect_service(&dac_stream_conn, 0);
    stream_connection_enable(&dac_stream_conn, true);

    for(;;)
    {
        toggle_led(LED2);
        dac_stream_start();
        sleep(1);
        dac_stream_stop();
        sleep(1);
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
