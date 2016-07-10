
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

#include "leds.h"
#include "sdcard_diskio.h"
#include "cutensils.h"


static disk_interface_t sddisk;
static logger_t log;
bool device_init_done = false;

void dump_task_info()
{
	char buffer[1024];
	vTaskList(buffer);
	log_info(&log, buffer);
}

void test()
{
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

	pthread_exit(0);
}

int main(void)
{
	flash_led(LED1);

	log_init(&log, "main");

    // init filesystem
    sdcard_mount(&sddisk, 0);

	// start demo app
    pthread_t app_thread;
	pthread_attr_t app_attr;
	pthread_attr_init(&app_attr);
	pthread_attr_setstacksize(&app_attr, 384);
	pthread_attr_setdetachstate(&app_attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&app_thread, &app_attr, (void*(*)(void*))test, NULL);
	pthread_attr_destroy(&app_attr);

	pthread_exit(0);
	return 0;
}
