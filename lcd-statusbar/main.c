
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
#include "builtins.h"

#include "lcd.h"
#include "lcd_backlight.h"
#include "graphics.h"
#include "touch_panel.h"
#include "statusbar.h"
#include "touch_key.h"

void init_devices(void* p);

#define  init_devices_task() xTaskCreate(init_devices,"init",configMINIMAL_STACK_SIZE + 192, NULL, tskIDLE_PRIORITY + 1, NULL)

static shellserver_t sh;
static netconf_t netconf;
static logger_t mainlog;

void init_devices(void* p)
{
    (void)p;

    // init logger
    log_init(&mainlog, "main");

    lcd_init();
    graphics_init();
    touch_panel_init();
    lcd_backlight_init();
    lcd_backlight_auto_off(false);
    lcd_backlight_enable();
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

    install_builtin_cmds(&sh);
    install_fs_cmds(&sh);
    install_net_cmds(&sh);
    install_os_cmds(&sh);

    if(start_shell(&sh, NULL, DEFAULT_SHELL_CONFIG_PATH, true, true, -1, -1) == -1)
        log_info(&mainlog, "shell init falied...");

    log_info(&mainlog, "service init done...");

    vTaskDelete(NULL);
}

int main(void)
{
    flash_led(LED1);
    init_devices_task();
    vTaskStartScheduler();
    return 0;
}
