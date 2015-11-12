

#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

#include "leds.h"
#include "sdfs.h"
#include "net.h"
#include "cutensils.h"
#include "nutensils.h"
#include "http_server.h"
#include "http_api_demo.h"


static netconf_t netconf;
static logger_t log;
static httpserver_t httpd;


int main(void)
{
    flash_led(LED1);

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

	if(init_http_server(&httpd, DEFAULT_HTTPSERVER_CONF_PATH, get_http_api_members()) == -1)
		log_error(&log, "http server init failed");

	log_info(&log, "service init done...");

	pthread_exit(0);
    return 0;
}
