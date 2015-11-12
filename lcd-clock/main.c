
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

#include "leds.h"
#include "cutensils.h"
#include "lcd.h"
#include "lcd_backlight.h"
#include "graphics.h"
#include "clock.h"

logger_t mainlog;

int main(void)
{
	flash_led(LED1);

	log_init(&mainlog, "main");

	// init lcd
	lcd_init();
	graphics_init();
	lcd_backlight_init();
	lcd_backlight_auto_off(false);
	lcd_backlight_enable();
	set_background_colour(LIGHT_ORANGE);

	clock_init(true, (point_t){300, 48}, (point_t){10, 10});

	pthread_exit(0);

	return 0;
}
