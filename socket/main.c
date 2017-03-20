

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
#include "sock_utils.h"

static disk_interface_t sddisk;
static netconf_t netconf;
static logger_t log;

void test()
{
    int fd;
    int length;
    char buf[128];
    char* http_get = "GET /hello HTTP/1.0\r\n\r\n";
    char* host = "192.168.20.103";
    int port = 8000;

    log_info(&log, "starting demo...");

    // loop doing an HTTP GET, printing the response
    for(;;)
    {
        fd = sock_connect(host, port, SOCK_STREAM, NULL);

        if(fd != -1)
        {
            send(fd, http_get, strlen(http_get), 0);

            do
            {
                length = recv(fd, buf, sizeof(buf)-1, 0);
                buf[length] = 0;
                if(length)
                printf(buf);
            }
            while(length > 0);

            closesocket(fd);
        }
        toggle_led(LED2);

        sleep(2);
    }

	pthread_exit(0);
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
    while(!wait_for_address(&netconf));

    // done
    log_info(&log, "device init done...");

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
