
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "text.h"
#include "cutensils.h"

#ifndef CLOCK_WIDGET_H_
#define CLOCK_WIDGET_H_

/**
 * example of creating a new widget type....
 */
typedef struct {
    char buffer[64];
    text_t text;
    point_t location;
    TaskHandle_t th;
    logger_t log;
}clock_widget_t;

clock_widget_t* clock_init(bool filled, point_t size, point_t location);

#endif // CLOCK_WIDGET_H_
