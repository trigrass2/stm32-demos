
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "clock.h"

static void clock_task(void* task_params)
{
    clock_widget_t* clock = (clock_widget_t*)task_params;

    time_t t;
    struct tm* lt;

    for(;;)
    {
        text_blank_text(&clock->text, clock->location);
        t = time(NULL);
        lt = localtime(&t);
        strftime(clock->buffer, sizeof(clock->buffer), "%H:%M:%S", lt);
        text_update_text(&clock->text, clock->buffer, clock->location);

        log_info(&clock->log, clock->buffer);

        sleep(1);
    }
}


clock_widget_t* clock_init(bool filled, point_t size, point_t location)
{
    clock_widget_t* clock = malloc(sizeof(clock_widget_t));

    if(clock)
    {
        log_info(&clock->log, "initializing clock");

        text_init(&clock->text, size, clock->buffer, 5);
        text_set_filled(&clock->text, filled);
        text_set_justification(&clock->text, JUSTIFY_CENTRE);

        // select font
        if(size.y >= 15 && size.y < 23)
            text_set_font(&clock->text, &Ubuntu_16);
        else if(size.y >= 23 && size.y < 31)
            text_set_font(&clock->text, &Ubuntu_24);
        else if(size.y >= 31 && size.y < 47)
            text_set_font(&clock->text, &Ubuntu_32);
        else if(size.y >= 47 && size.y < 64)
            text_set_font(&clock->text, &Ubuntu_48_bold);
        else
            text_set_font(&clock->text, &Ubuntu_64);

        clock->location = location;

        if(xTaskCreate(clock_task, "clock", configMINIMAL_STACK_SIZE + 128, clock, tskIDLE_PRIORITY + 1, &clock->th) == pdPASS)
        {
            log_info(&clock->log, "started clock task");
            text_draw(&clock->text, clock->location);
        }
        else
        {
            log_error(&clock->log, "error starting clock task");
            free(clock);
            clock = NULL;
        }
    }
    else
        log_error(&clock->log, "error initializing clock");

    return clock;
}
