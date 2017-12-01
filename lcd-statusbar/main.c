
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

#include "leds.h"
#include "sdcard_diskio.h"
#include "net.h"
#include "logger.h"
#include "shell.h"

#include "shell.h"
#include "fs_cmds.h"
#include "net_cmds.h"
#include "os_cmds.h"
#include "builtins.h"

#include "lcd.h"
#include "lcd_backlight.h"
#include "graphics.h"
#include "touch_panel.h"
#include "statusbar.h"
#include "touch_key.h"

static disk_interface_t sddisk;
static shellserver_t sh;
static netconf_t netconf;
static logger_t mainlog;

typedef struct {
	char text_buffer[16];
	int count;
	text_t display;
	touch_key_t up;
	touch_key_t down;
	bool longpress;
} appdata_t;

void touch_callback(touch_key_t* tc)
{
	appdata_t* ad = (appdata_t*)tc->handler.appdata;
	int c = ad->count;

	switch(touch_key_get_press_type(tc))
	{
		case KEY_DOWN:
			if(tc == &ad->down) {
				ad->count--;
			}
			else {
				ad->count++;
			}
		break;
		case KEY_UP:
			ad->longpress = false;
		break;
		case KEY_LONG_PRESS:
			ad->longpress = true;
		break;
		case KEY_HOLD:
			if(ad->longpress) {
				if(tc == &ad->down) {
					ad->count--;
				}
				else {
					ad->count++;
				}
			}
		break;
		default:
		break;
	}

	if(c != ad->count) {
		text_blank_text(&ad->display, (point_t){80-5, 60}); // blank old
		sprintf(ad->text_buffer, "Count: %d", ad->count);
		text_redraw_text(&ad->display, (point_t){80-5, 60}); // draw new
	}
}

void demo(appdata_t* ad)
{
    statusbar_init();

	ad->longpress = false;
	ad->count = 0;
	sprintf(ad->text_buffer, "Count: %d", ad->count);

	text_init(&ad->display, (point_t){170, 50}, ad->text_buffer, 0);
	text_set_justification(&ad->display, JUSTIFY_CENTRE);
	text_draw(&ad->display, (point_t){80-5, 60});

	touch_key_init(&ad->up, (point_t){160+5, 120}, (point_t){80, 50}, "UP", 0);
	touch_key_add(&ad->up, (touch_callback_t)touch_callback, ad);
	touch_key_enable(&ad->up, true);

	touch_key_init(&ad->down, (point_t){80-5, 120}, (point_t){80, 50}, "DN", 0);
	touch_key_add(&ad->down, (touch_callback_t)touch_callback, ad);
	touch_key_enable(&ad->down, true);
}

int main(void)
{
	appdata_t ad;

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

    demo(&ad);

    // init filesystem
    sdcard_mount(&sddisk, 0);

    // init networking
    net_config(&netconf, DEFAULT_RESOLV_CONF_PATH, DEFAULT_NETIF_CONF_PATH);
    net_init(&netconf);

    log_info(&mainlog, "device init done...");

    install_builtin_cmds(&sh);
    install_fs_cmds(&sh);
    install_net_cmds(&sh);
    install_os_cmds(&sh);

    if(start_shell(&sh, NULL, DEFAULT_SHELL_CONFIG_PATH, true, true, -1, -1, 0) == -1)
        log_info(&mainlog, "shell init falied...");

    log_info(&mainlog, "service init done...");

    pthread_exit(0);
    return 0;
}
