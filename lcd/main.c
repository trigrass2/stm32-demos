
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "leds.h"

#include "cutensils.h"

#include "lcd.h"
#include "graphics.h"
#include "text.h"


void init_devices(void* p);
void clock_task(void* p);

#define  init_devices_task() xTaskCreate(init_devices,"init",configMINIMAL_STACK_SIZE + 192, NULL, tskIDLE_PRIORITY + 1, NULL)


typedef struct {
    char buffer[64];
    shape_t background;
    text_t text;
    point_t location;
    TaskHandle_t th;
}clock_widget_t;


clock_widget_t* create_clock(colour_t bg_colour, colour_t txt_colour, bool filled, point_t size, point_t location)
{
    clock_widget_t* clock = malloc(sizeof(clock_widget_t));

    if(clock)
    {
        clock->background.type = SQUARE;                ///< defines the type of shape
        clock->background.fill_colour = bg_colour;      ///< the colour of the shape
        clock->background.border_colour = bg_colour;    ///< the colour of the shape border
        clock->background.fill = filled;                ///< if set, fills the shape, if false just draws an border.
        clock->background.size = size;               ///< the size of the shape (bounding rectangle of non rectangles)
        clock->background.radius = 5;

        clock->text.buffer = clock->buffer;
        clock->text.colour = txt_colour;
        clock->text.justify = JUSTIFY_CENTRE;
        clock->text.shape = &clock->background;
        if(size.y >= 15 && size.y < 23)
            clock->text.font = &Ubuntu_16;
        else if(size.y >= 23 && size.y < 31)
            clock->text.font = &Ubuntu_24;
        else if(size.y >= 31 && size.y < 47)
            clock->text.font = &Ubuntu_32;
        else if(size.y >= 47 && size.y < 64)
            clock->text.font = &Ubuntu_48_bold;
        else
            clock->text.font = &Ubuntu_64;

        clock->location = location;

        if(xTaskCreate(clock_task, "clock", configMINIMAL_STACK_SIZE + 64, clock, tskIDLE_PRIORITY + 1, &clock->th) == pdPASS)
        {
            printf("started clock task\n");
            draw_textbox(&clock->text, clock->location);
        }
        else
        {
            free(clock);
            clock = NULL;
        }
    }

    return clock;
}

void clock_task(void* task_params)
{
    clock_widget_t* clock = (clock_widget_t*)task_params;

    time_t t;
    struct tm* lt;

    for(;;)
    {
        t = time(NULL);
        lt = localtime(&t);
        strftime(clock->buffer, sizeof(clock->buffer), "%H:%M:%S", lt);
        text_update_text(&clock->text, clock->buffer, clock->location);

        printf("%s\n", clock->buffer);

        sleep(1);
        text_blank_text(&clock->text, clock->location);
    }
}


void init_devices(void* p)
{
	(void)p;

	// init lcd
	lcd_init();
	graphics_init();
	lcd_backlight(1);
    set_background_colour(LIGHT_ORANGE);

    create_clock(DARK_GREEN, LIGHT_BLUE, true, (point_t){320, 48}, (point_t){0, 0});

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
