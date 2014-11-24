
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
void circles_task(void* p);

#define  init_devices_task() xTaskCreate(init_devices,"init",configMINIMAL_STACK_SIZE + 192, NULL, tskIDLE_PRIORITY + 1, NULL)
#define  init_clock_task() xTaskCreate(clock_task,"clock",configMINIMAL_STACK_SIZE + 64, NULL, tskIDLE_PRIORITY + 1, NULL)
#define  init_circles_task() xTaskCreate(circles_task,"circles",configMINIMAL_STACK_SIZE + 64, NULL, tskIDLE_PRIORITY + 1, NULL)

char clock_buffer[64];

static shape_t clock_background = {
    .type = SQUARE,                     ///< defines the type of shape
    .fill_colour = DARK_GREEN,          ///< the colour of the shape
    .border_colour = DARK_GREEN,        ///< the colour of the shape border
    .fill = true,                       ///< if set, fills the shape, if false just draws an border.
    .size = {320, 32},         ///< the size of the shape (bounding rectangle of non rectangles)
    .radius = 5
};

static text_t clock_text = {
    .buffer = clock_buffer,
    .colour = LIGHT_BLUE,
    .font = &Ubuntu_24,
    .justify = JUSTIFY_CENTRE,
    .shape = &clock_background
};

//static shape_t random_circle = {
//    .type = CIRCLE,                     ///< defines the type of shape
//    .fill_colour = WHITE,               ///< the colour of the shape
//    .border_colour = WHITE,             ///< the colour of the shape border
//    .fill = true,                       ///< if set, fills the shape, if false just draws an border.
//    .size = (point_t){20, 30},          ///< the size of the shape (bounding rectangle of non rectangles)
//    .radius = 5
//};

void circles_task(void* p)
{
    (void)p;
    for(;;)
    {
        sleep(1);
    }
}

void clock_task(void* p)
{
    (void)p;
    time_t t;
    struct tm* lt;

    draw_textbox(&clock_text, (point_t){0, 208});

    for(;;)
    {
        t = time(NULL);
        lt = localtime(&t);
        strftime(clock_buffer, sizeof(clock_buffer), "%Y-%m-%d %H:%M:%S%z", lt);
        text_update_text(&clock_text, clock_buffer, (point_t){0, 208});
        sleep(1);
        text_blank_text(&clock_text, (point_t){0, 208});
    }
}


void init_devices(void* p)
{
	(void)p;

	// init logger
//	log_add_handler(STDOUT_FILENO);

	// init lcd
	lcd_init();
	graphics_init();
	lcd_backlight(1);
    set_background_colour(BLACK);

    init_clock_task();
    init_circles_task();

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
