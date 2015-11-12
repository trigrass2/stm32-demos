
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

#include "leds.h"
#include "cutensils.h"

#include "lcd.h"
#include "lcd_backlight.h"
#include "graphics.h"
#include "touch_panel.h"
#include "panel_meter.h"
#include "touch_key.h"

static logger_t mainlog;

#define BOX_LOCATION    (point_t){50, 60}
#define BOX_SIZE        (point_t){220, 70}
#define BOX_MAIN_FONT   &Digital_7_Italic_64
#define BOX_UNIT_FONT   &Ubuntu_20

char buffer[16];
static panel_meter_t panelmeter;

char* panelmeter_touch_appdata = "panel meter";

void touch_key_callback(touch_key_t* key)
{
    printf("touch key: %s\n", touch_key_get_appdata(key));
    printf("touch type: %s\n", touch_panel_get_press_type_string(&key->handler));
    printf("touch appdata: %s\n", touch_key_get_appdata(key));
}

int main(void)
{
    flash_led(LED1);

    // init logger
	log_init(&mainlog, "main");

	lcd_init();
	graphics_init();
	touch_panel_init();
	lcd_backlight_init();
	lcd_backlight_auto_off(false);
	lcd_backlight_enable();
	set_background_colour(BLACK);

	panel_meter_init(&panelmeter, buffer, BOX_LOCATION, BOX_SIZE, true, "%.3f", "C", BOX_MAIN_FONT, BOX_UNIT_FONT);
	panel_meter_enable_touch(&panelmeter, (touch_callback_t)touch_key_callback, panelmeter_touch_appdata);

	float val = 0;
	while(1)
	{
		printf("val %.3f\n", (double)val);
		panel_meter_update(&panelmeter, val);
		val += 0.1;
		sleep(1);
	}

	pthread_exit(0);

    return 0;
}
