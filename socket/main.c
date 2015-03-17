

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


void init_devices(void* p);
void test(void*p);

#define  init_devices_task() xTaskCreate(init_devices, "init", configMINIMAL_STACK_SIZE + 192, NULL, tskIDLE_PRIORITY + 1, NULL)
#define  test_task() xTaskCreate(test, "test", configMINIMAL_STACK_SIZE + 128, NULL, tskIDLE_PRIORITY + 1, NULL)

static netconf_t netconf;
static logger_t log;

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

    // done
    log_info(&log, "device init done...");
    test_task();
    vTaskDelete(NULL);
}

void test(void*p)
{
    (void)p;
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
}

int main(void)
{
    flash_led(LED1);

    init_devices_task();

    vTaskStartScheduler();

    printf("Error: Scheduler Exited\n");

    return 0;
}
