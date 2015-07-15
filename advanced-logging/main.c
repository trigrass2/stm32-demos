

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

#define  init_devices_task() xTaskCreate(init_devices, "init", configMINIMAL_STACK_SIZE + 192, NULL, tskIDLE_PRIORITY + 1, NULL)
#define  test_task() xTaskCreate(test, "test", configMINIMAL_STACK_SIZE + 128, NULL, tskIDLE_PRIORITY + 1, NULL)

static netconf_t netconf;
static logger_t log;
static shellserver_t shell;

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

    // sure the log directory exists
    mkdir("/var/log", 0777);
    // add file logger - can add any regular file, device file, tcp client socket, or STDOUT_FILENO/STDERR_FILENO
    int syslog = open("/var/log/syslog", O_WRONLY|O_APPEND|O_CREAT);
    if(syslog != -1)
        log_add_handler(syslog);
    else
        log_error(&log, "failed to open syslog...");

    // adding a udp handler is a special case
    int udplog = add_udp_log_handler("10.0.2.15", 32000);
    if(udplog == -1)
        log_error(&log, "failed to start udp log...");

    if(start_shell(&shell, NULL, DEFAULT_SHELL_CONFIG_PATH, true, true, -1, -1) != -1)
    {
        install_fs_cmds(&shell);
        install_net_cmds(&shell);
        install_os_cmds(&shell);
    }

    // done
    log_info(&log, "device init done...");
    test_task();
    vTaskDelete(NULL);
}

void test(void*p)
{
    (void)p;
    int count = 0;
    logger_t another_log;

    // to add context to the log files, use different logger context structures.
    log_init(&another_log, "another-log");

    log_info(&log, "starting demo...");

    for(;;)
    {
        log_info(&log, "demo %s messsage %d", "info", count);
        log_debug(&log, "demo %s messsage %d", "debug", count);
        log_edebug(&log, "demo %s messsage %d", "edebug", count);
        log_warning(&log, "demo %s messsage %d", "warning", count);
        log_error(&log, "demo %s messsage %d", "error", count);
        log_info(&another_log, "demo %s messsage %d", "info", count);
        log_debug(&another_log, "demo %s messsage %d", "debug", count);
        log_edebug(&another_log, "demo %s messsage %d", "edebug", count);
        log_warning(&another_log, "demo %s messsage %d", "warning", count);
        log_error(&another_log, "demo %s messsage %d", "error", count);
        toggle_led(LED2);
        sleep(5);
    }
}

int main(void)
{
    flash_led(LED1);

    init_devices_task();

    vTaskStartScheduler();

    printf("Error: Scheduler Exited\n");

    return 0;
}
