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

const http_api_t demo_http_api_status = {"status", demo_http_api_status_func};
const http_api_t demo_http_api_info = {"info", demo_http_api_info_func};

const http_api_t* http_api_members[] = {
    &demo_http_api_status,
    &demo_http_api_info,
    NULL
};

const http_api_t** get_http_api_members()
{
    return http_api_members;
}

/**
 * @brief   RRC Power Supply Access
 *
 * Responds to a GET by sending power supply information.
 *
 @code
{
    "enabled":boolean,
    "power":int,
    "voltage":int,
    "current":int
}
 @endcode
 *
 * Responds to a POST by changing the state of the supply.
 *
 @code
{
    "enabled":boolean,
    "voltage":int
}
 @endcode
 */
int demo_http_api_status_func(int fdes, int content_length, char* buffer, int size)
{
    (void)buffer;           // a pointer to memory that may be used as a work area
    (void)content_length;   // if there us incoming data, this specifies the length that needs to be received.
    (void)size;             // the size in bytes of the work area 'buffer'

    FILE* f = fdopen(fdes, "w");

    fprintf(f, "{\"online\":%d}", 1);

    return 0;
}

int demo_http_api_info_func(int fdes, int content_length, char* buffer, int size)
{
    (void)buffer;           // a pointer to memory that may be used as a work area
    (void)content_length;   // if there us incoming data, this specifies the length that needs to be received.
    (void)size;             // the size in bytes of the work area 'buffer'

    FILE* f = fdopen(fdes, "w");

    fprintf(f, "{\"fwv\":\"%s\",\"hwv\":\"%s\",\"kernel\":\"%s-%s\"}", PROJECT_VERSION, BOARD, OPERATING_SYSTEM, KERNEL_VERSION);

    return 0;
}






