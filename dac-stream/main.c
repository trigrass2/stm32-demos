
#include <unistd.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "leds.h"
#include "dac_stream.h"

void dac_stream_callback(uint16_t* buffer, uint16_t length, uint8_t channels, uint8_t channel)
{
    printf("%x %d %d %d\n", buffer, length, channels, channel);
}

stream_connection_t dac_stream_conn = {
        .process = dac_stream_callback,
        .name = "abc",
        .enabled = true
};

void test_task(void*p)
{
    (void)p;

    dac_stream_init();
    dac_stream_set_samplerate(2000);
    dac_stream_connect_service(&dac_stream_conn);

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
