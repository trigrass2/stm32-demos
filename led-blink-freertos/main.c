

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "leds.h"

void test_task(void*p)
{
    (void)p;

    for(;;)
    {
        toggle_led(LED2);
        vTaskDelay(250/portTICK_RATE_MS);
    }
}

#define  start_test_task() xTaskCreate(test_task,\
                                        "test task",\
                                        configMINIMAL_STACK_SIZE + 1024, \
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
