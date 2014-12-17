
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "leds.h"
#include "sdfs.h"
#include "net.h"
#include "cutensils.h"
#include "nutensils.h"

#include "shell.h"
#include "fs_cmds.h"
#include "net_cmds.h"
#include "os_cmds.h"

#include "lcd.h"
#include "graphics.h"
#include "touch_panel.h"
#include "statusbar.h"
#include "panel_meter.h"
#include "touch_key.h"

void init_devices(void* p);

#define  init_devices_task() xTaskCreate(init_devices,"init",configMINIMAL_STACK_SIZE + 192, NULL, tskIDLE_PRIORITY + 1, NULL)

static shellserver_t sh;
static netconf_t netconf;
static logger_t mainlog;


#define BOX_LOCATION    {30, 60}
#define BOX_SIZE        {180, 54}
#define BOX_MAIN_FONT   Digital_7_Italic_64
#define BOX_UNIT_FONT   Ubuntu_20

char buffer[16];

static panel_meter_t panelmeter = {
    .prescision = "%.2f",
    .location = BOX_LOCATION,
    .units = "V",
    .units_font = &BOX_UNIT_FONT,
    .background = {
        .fill_colour = MID_GREEN,
        .border_colour = MID_GREEN,
        .size = BOX_SIZE
    },
    .textbox = {
        .font = &BOX_MAIN_FONT,
        .colour = GREEN
    }
};

static touch_key_t meter_key = {
    .text = &panelmeter.textbox,
    .alt_colour = LIGHT_GREEN,
};

static touch_handler_t meter_key_handler = {
    .location = BOX_LOCATION,
    .keydata = &meter_key
};

char* panelmeter_touch_appdata = "panel meter";

void touch_key_callback(touch_handler_t* key)
{
    if(touch_key_is(&meter_key_handler, key))
    {
        printf("touch key: %s\n", touch_get_appdata(key));
        printf("touch type: %s\n", touch_get_press_type_string(key));
    }
}

void init_devices(void* p)
{
    (void)p;

    // init logger
    log_init(&mainlog, "main");

    lcd_init();
    graphics_init();
    touch_init();
    lcd_backlight(1);
    set_background_colour(BLACK);
    statusbar_init();

    // init filesystem
    sdfs_init();
    log_info(&mainlog, "wait for filesystem...");
    while(!sdfs_ready());

    // init networking
    net_config(&netconf, DEFAULT_RESOLV_CONF_PATH, DEFAULT_NETIF_CONF_PATH);
    net_init(&netconf);

    log_info(&mainlog, "device init done...");

    if(start_shell(&sh, DEFAULT_SHELL_CONFIG_PATH) != -1)
    {
        install_fs_cmds(&sh);
        install_net_cmds(&sh);
        install_os_cmds(&sh);
    }
    else
        log_info(&mainlog, "shell init falied...");

    log_info(&mainlog, "service init done...");

    init_panel_meter(&panelmeter, buffer, sizeof(buffer), true);
    touch_set_callback(&meter_key_handler, touch_key_callback);
    touch_set_appdata(&meter_key_handler, panelmeter_touch_appdata);
    touch_add_key(&meter_key_handler);
    touch_enable_key(&meter_key_handler, true);

    float val = 0;
    while(1)
    {
        update_panel_meter(&panelmeter, val);
        val += 0.1;
        sleep(1);
    }

    vTaskDelete(NULL);
}

int main(void)
{
    flash_led(LED1);
    init_devices_task();
    vTaskStartScheduler();
    return 0;
}
