

#include <sys/socket.h>
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
#include "net_cmds.h"
#include "fs_cmds.h"
#include "os_cmds.h"
#include "builtins.h"

/**************************
 *
 * Demo may be broken :(
 *
 ***************************/

static disk_interface_t sddisk;
static netconf_t netconf;
static logger_t log;
static shellserver_t shell;


void test()
{
    int count = 0;
    logger_t another_log;

    // to add context to the log files, use different logger context structures.
    log_init(&another_log, "another-log");

    log_info(&log, "starting demo...");

    for(;;)
    {
        log_info(&log, "demo %s messsage %d", "info", count);
        log_debug(&log, "demo %s messsage %d", "debug", count);
        log_warning(&log, "demo %s messsage %d", "warning", count);
        log_error(&log, "demo %s messsage %d", "error", count);
        log_info(&another_log, "demo %s messsage %d", "info", count);
        log_debug(&another_log, "demo %s messsage %d", "debug", count);
        log_warning(&another_log, "demo %s messsage %d", "warning", count);
        log_error(&another_log, "demo %s messsage %d", "error", count);
        toggle_led(LED2);
        sleep(5);
    }
}

int main(void)
{
    flash_led(LED1);

    // init logger
	log_init(&log, "main");

	// init filesystem
	sdcard_mount(&sddisk, 0);

	// init networking
	net_config(&netconf, DEFAULT_RESOLV_CONF_PATH, DEFAULT_NETIF_CONF_PATH);
	net_init(&netconf);
	

	// sure the log directory exists
	mkdir("/var", 0777);
	mkdir("/var/log", 0777);

	// add file logger - can add any regular file, device file, tcp client socket, or STDOUT_FILENO/STDERR_FILENO
	int syslog = open("/var/log/syslog", O_WRONLY|O_APPEND|O_CREAT);
	if(syslog != -1)
	{
		log_add_handler(syslog);
	}
	else
	{
		log_error(&log, "failed to open syslog...");
	}

	// adding a udp handler is a special case
	int udplog = add_udp_log_handler("192.168.20.112", 32000);

	if(udplog == -1)
	{
		log_error(&log, "failed to start udp log...");
	}


	install_builtin_cmds(&shell);
	install_fs_cmds(&shell);
	install_net_cmds(&shell);
	install_os_cmds(&shell);

	if(start_shell(&shell, NULL, DEFAULT_SHELL_CONFIG_PATH, true, true, -1, -1, 0) == -1)
	{
		log_error(&log, "failed to start shell...");
	}

	// done
	log_info(&log, "device init done...");

	// start demo task
    pthread_t app_thread;
	pthread_attr_t app_attr;
	pthread_attr_init(&app_attr);
	pthread_attr_setstacksize(&app_attr, 256);
	pthread_attr_setdetachstate(&app_attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&app_thread, &app_attr, (void*(*)(void*))test, NULL);
	pthread_attr_destroy(&app_attr);

	pthread_exit(0);
    return 0;
}
