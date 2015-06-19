/*
 * http_api_demo.c
 *
 *  Created on: 22/03/2015
 *      Author: mike
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "system.h"
#include "http_api_demo.h"


int demo_http_api_status_func(int fdes, int content_length, char* buffer, int size);
int demo_http_api_info_func(int fdes, int content_length, char* buffer, int size);
int demo_http_api_fileserver_func(int fdes, int content_length, char* buffer, int size);

const http_api_t demo_http_api_status = {"status", demo_http_api_status_func};
const http_api_t demo_http_api_info = {"info", demo_http_api_info_func};
const http_api_t demo_http_api_files = {"files", demo_http_api_fileserver_func};

const http_api_t* http_api_members[] = {
    &demo_http_api_status,
    &demo_http_api_info,
    &demo_http_api_files,
    NULL
};

const http_api_t** get_http_api_members()
{
    return http_api_members;
}

/**
 * sends the index.html file as raw text, just to demo file transfer.
 */
int demo_http_api_fileserver_func(int fdes, int content_length, char* buffer, int size)
{
    (void)content_length;   // if there us incoming data, this specifies the length that needs to be received.
    int length;
    int file = open("/var/lib/httpd/index.html", O_RDONLY);

    if(file != -1)
    {
        length = size;
        while(length == size)
        {
            length = read(file, buffer, size);
            length = write(fdes, buffer, length);
        }
    }

    return 0;
}


/**
 * @brief   Device status API
 *
 * Responds to a GET by sending status information.
 *
 @code
{
    "time_s": int,          // time in s since the epoch
    "time_us": int,         // time in us past the second
    "rxpkt" int,            // ip packets received
    "txpkt" int,            // ip packets transmitted
}
 @endcode
 *
 */
int demo_http_api_status_func(int fdes, int content_length, char* buffer, int size)
{
    (void)buffer;           // a pointer to memory that may be used as a work area
    (void)content_length;   // if there us incoming data, this specifies the length that needs to be received.
    (void)size;             // the size in bytes of the work area 'buffer'
    struct timeval tv;

    gettimeofday(&tv, NULL);

    FILE* f = fdopen(fdes, "w");

    fprintf(f, "{\"time_s\":%u, \"time_us\":%u, \"txpkt\": %u, \"rxpkt\":%u}",
            tv.tv_sec, tv.tv_usec, net_ip_packets_sent(), net_ip_packets_received());

    return 0;
}

/**
 * @brief   Device info API
 *
 * Responds to a GET by sending device information.
 *
 @code
{
    "fwv":string,           // firmware version
    "hwv":string,           // device hardware (board name)
    "kernel": string        // os kernel version
}
 @endcode
 *
 */
int demo_http_api_info_func(int fdes, int content_length, char* buffer, int size)
{
    (void)buffer;           // a pointer to memory that may be used as a work area
    (void)content_length;   // if there us incoming data, this specifies the length that needs to be received.
    (void)size;             // the size in bytes of the work area 'buffer'

    FILE* f = fdopen(fdes, "w");

    fprintf(f, "{\"fwv\":\"%s\",\"hwv\":\"%s\",\"kernel\":\"%s-%s\"}", PROJECT_VERSION, BOARD, OPERATING_SYSTEM, KERNEL_VERSION);

    return 0;
}






