

#include <sys/socket.h>
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
#include "net_cmds.h"
#include "fs_cmds.h"
#include "os_cmds.h"


void init_devices(void* p);
void test(void*p);
int custom_cmd_handler(int fdes, const char** args, unsigned char nargs);

#define  init_devices_task() xTaskCreate(init_devices, "init", configMINIMAL_STACK_SIZE + 192, NULL, tskIDLE_PRIORITY + 1, NULL)

static netconf_t netconf;
static logger_t log;
static shellserver_t shell;

shell_cmd_t sh_custom_cmd = {
     .name = "mycmd",
     .usage = "demo shell command " SHELL_NEWLINE
"flags:" SHELL_NEWLINE
" -a  print out the argument given directly after this flag, if any" SHELL_NEWLINE
" -b  this is a binary flag, if specified prints a special message",
     .cmdfunc = custom_cmd_handler
};

int custom_cmd_handler(int fdes, const char** args, unsigned char nargs)
{
    const char* arg_a = arg_by_switch("-a", args, nargs);
    if(arg_a)
    {
        send(fdes, "got arg -a: ", sizeof("got arg -a: ")-1, 0);
        send(fdes, arg_a, strlen(arg_a), 0);
        send(fdes, SHELL_NEWLINE, sizeof(SHELL_NEWLINE)-1, 0);
    }

    if(has_switch("-b", args, nargs))
    {
        send(fdes, "got arg -b yeay!"SHELL_NEWLINE, sizeof("got arg -b yeay!"SHELL_NEWLINE)-1, 0);
    }

    return SHELL_CMD_EXIT;
}

void init_devices(void* p)
{
    (void)p;

    // init logger
    log_init(&log, "main");

    // init filesystem
    sdfs_init();
    log_info(&log, "wait for filesystem...");
    while(!sdfs_ready());

    // init networking
    net_config(&netconf, DEFAULT_RESOLV_CONF_PATH, DEFAULT_NETIF_CONF_PATH);
    net_init(&netconf);
    while(!wait_for_address(&netconf));

    log_info(&log, "device init done...");

    if(start_shell(&shell, DEFAULT_SHELL_CONFIG_PATH))
    {
        install_fs_cmds(&shell);
        install_net_cmds(&shell);
        install_os_cmds(&shell);

        register_command(&shell, &sh_custom_cmd, NULL, NULL, NULL);
    }

    log_info(&log, "service init done...");

    vTaskDelete(NULL);
}

int main(void)
{
    flash_led(LED1);

    init_devices_task();

    vTaskStartScheduler();

    printf("Error: Scheduler Exited\n");

    return 0;
}
