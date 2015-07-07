
#define DEMO_WITH_ETHERNET_INCLUDED     USE_DRIVER_LWIP_NET

#if DEMO_WITH_ETHERNET_INCLUDED
#include <sys/socket.h>
#include "net.h"
#include "net_cmds.h"
#endif
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
#include "cutensils.h"
#include "nutensils.h"
#include "shell.h"
#include "fs_cmds.h"
#include "os_cmds.h"

#include "usart.h"


void init_devices(void* p);
int custom_cmd_handler(int fdes, const char** args, unsigned char nargs);

#define  init_devices_task() xTaskCreate(init_devices, "init", configMINIMAL_STACK_SIZE + 512, NULL, tskIDLE_PRIORITY + 1, NULL)

#if DEMO_WITH_ETHERNET_INCLUDED
static netconf_t netconf;
#endif
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
        write(fdes, "got arg -a: ", sizeof("got arg -a: ")-1);
        write(fdes, arg_a, strlen(arg_a));
        write(fdes, SHELL_NEWLINE, sizeof(SHELL_NEWLINE)-1);
    }

    if(has_switch("-b", args, nargs))
    {
        write(fdes, "got arg -b yeay!"SHELL_NEWLINE, sizeof("got arg -b yeay!"SHELL_NEWLINE)-1);
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

#if DEMO_WITH_ETHERNET_INCLUDED
    // init networking
    net_config(&netconf, DEFAULT_RESOLV_CONF_PATH, DEFAULT_NETIF_CONF_PATH);
    net_init(&netconf);
    while(!wait_for_address(&netconf));
#endif

    // install usart device to use for shell
    usart_init(CONSOLE_USART, "/dev/ttyS0", false);

    log_info(&log, "device init done...");

    // install shell commands
    install_fs_cmds(&shell);
#if DEMO_WITH_ETHERNET_INCLUDED
    install_net_cmds(&shell);
#endif
    install_os_cmds(&shell);
    install_builtin_cmds(&shell);

    register_command(&shell, &sh_custom_cmd, NULL, NULL, NULL);
    int fdes = open("/dev/ttyS0", O_RDWR, 128);
    shell_instance(&shell, fdes, fdes);

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
