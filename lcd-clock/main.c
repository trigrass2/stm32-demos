
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "leds.h"
#include "cutensils.h"
#include "lcd.h"
#include "lcd_backlight.h"
#include "graphics.h"
#include "clock.h"


void init_devices(void* p);

#define  init_devices_task() xTaskCreate(init_devices,"init",configMINIMAL_STACK_SIZE + 192, NULL, tskIDLE_PRIORITY + 1, NULL)

logger_t mainlog;

void init_devices(void* p)
{
	(void)p;

	log_init(&mainlog, "main");

	// init lcd
	lcd_init();
	graphics_init();
    lcd_backlight_init();
    lcd_backlight_auto_off(false);
    lcd_backlight_enable();
    set_background_colour(LIGHT_ORANGE);

    clock_init(true, (point_t){300, 48}, (point_t){10, 10});

	vTaskDelete(NULL);
}

int main(void)
{
	flash_led(LED1);

	init_devices_task();

	vTaskStartScheduler();

	return 0;
}
