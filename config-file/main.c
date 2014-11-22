
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
#include "cutensils.h"

void test(void*p);

#define  init_devices_task() xTaskCreate(init_devices,"init",configMINIMAL_STACK_SIZE + 256, NULL, tskIDLE_PRIORITY + 1, NULL)
#define  test_task() xTaskCreate(test,"test",configMINIMAL_STACK_SIZE + 256, NULL, tskIDLE_PRIORITY + 1, NULL)

static logger_t log;
bool device_init_done = false;

void dump_task_info()
{
	char buffer[1024];
	vTaskList(buffer);
	log_info(&log, buffer);
}

void init_devices(void* p)
{
	(void)p;

	log_add_handler(STDOUT_FILENO);
	log_init(&log, "main");

	sdfs_init();
	log_info(&log, "wait for filesystem...");
	while(!sdfs_ready());

	test_task();

	vTaskDelete(NULL);
}

void test(void*p)
{
    (void)p;
    bool result;
    const uint8_t* filename = (const uint8_t*)"/home/user/test.conf";
    uint8_t buffer[64];
    config_parser_t cfg;

    for(;;)
    {
        toggle_led(LED2);

        log_info(&log, "remove file %s", filename);

        // delete the file
        unlink((const char*)filename);

        // check the file is not present
        if(open_config_file(&cfg, buffer, sizeof(buffer), filename))
        {
            while(get_next_config(&cfg))
            	log_info(&log, "read %s=%s", get_config_key(&cfg), get_config_value(&cfg));
            close_config_file(&cfg);
        }
        else
            log_info(&log, "file %s removed successfully", filename);

        // add to a new file
        result = add_config_entry(buffer, sizeof(buffer),
        							filename,
									(const uint8_t*)"testkey",
									(const uint8_t*)"testvalue");
        log_info(&log, "wrote %s=%s to %s, result=%d", "testkey", "testvalue", filename, result);

        result = add_config_entry(buffer, sizeof(buffer),
        							filename,
									(const uint8_t*)"testkey1",
									(const uint8_t*)"testvalue1");
        log_info(&log, "wrote %s=%s to %s, result=%d", "testkey1", "testvalue1", filename, result);

        // check the file is now present with
        if(open_config_file(&cfg, buffer, sizeof(buffer), filename))
        {
            while(get_next_config(&cfg))
            	log_info(&log, "read %s=%s", get_config_key(&cfg), get_config_value(&cfg));
            close_config_file(&cfg);
        }

        // edit within file
        result = edit_config_entry(buffer, sizeof(buffer),
                                    filename,
                                    (const uint8_t*)"testkey",
                                    (const uint8_t*)"newtestvalue");
        log_info(&log, "wrote %s=%s to %s, result=%d", "testkey", "testvalue", filename, result);

        result = edit_config_entry(buffer, sizeof(buffer),
                                    filename,
                                    (const uint8_t*)"testkey1",
                                    (const uint8_t*)"newtestvalue1");
        log_info(&log, "wrote %s=%s to %s, result=%d", "testkey1", "testvalue1", filename, result);

        // check the file is now present with new values
        if(open_config_file(&cfg, buffer, sizeof(buffer), filename))
        {
            while(get_next_config(&cfg))
                log_info(&log, "read %s=%s", get_config_key(&cfg), get_config_value(&cfg));
            close_config_file(&cfg);
        }

        sleep(10);
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
