

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


int custom_cmd_handler(int fdes, const char** args, unsigned char nargs);

static disk_interface_t sddisk;
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

	log_info(&log, "device init done...");

	install_builtin_cmds(&shell);
	install_fs_cmds(&shell);
	install_net_cmds(&shell);
	install_os_cmds(&shell);
	register_command(&shell, &sh_custom_cmd, NULL, NULL, NULL);

	start_shell(&shell, NULL, DEFAULT_SHELL_CONFIG_PATH, true, true, -1, -1, 0);

	log_info(&log, "service init done...");

	pthread_exit(0);

    return 0;
}
