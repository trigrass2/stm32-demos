
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

static disk_interface_t sddisk;
static shellserver_t sh;
static netconf_t netconf;
static logger_t mainlog;

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

    statusbar_init();

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

    if(start_shell(&sh, NULL, DEFAULT_SHELL_CONFIG_PATH, true, true, -1, -1) == -1)
        log_info(&mainlog, "shell init falied...");

    log_info(&mainlog, "service init done...");

    pthread_exit(0);
    return 0;
}
