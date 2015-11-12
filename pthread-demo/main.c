
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "system.h"
#include "cutensils.h"
#include "leds.h"

typedef void*(*pf)(void*);

logger_t log;
pthread_attr_t attr;
pthread_t stuff_thread;
pthread_t config;

/**
 * this can be used to tune stack sizes ...
 * TODO how do I get the value of stack size, per task at runtime?
 */
void dump_task_info(logger_t* log)
{
	unsigned long uptime;
	int i;
	int ntasks = uxTaskGetNumberOfTasks();
	TaskStatus_t* state_table;
	state_table = malloc(ntasks * sizeof(TaskStatus_t));

	log_debug(log, "***********************************************");
	if(state_table)
	{
		uxTaskGetSystemState(state_table, ntasks, &uptime);
		log_debug(log, "Enabled Tasks: %d", ntasks);
		log_debug(log, "Up Time: %u", uptime);
		log_debug(log, "     state       hwm    uptime\tID\tname");
		for(i = 0; i < ntasks; i++)
			log_debug(log, "% 10d% 10d% 10d% 11d\t%s", state_table[i].eCurrentState, state_table[i].usStackHighWaterMark, state_table[i].ulRunTimeCounter, (uint32_t)state_table[i].xHandle, state_table[i].pcTaskName);
		free(state_table);
	}
	log_debug(log, "***********************************************");
}

void stuff(void* ctx)
{
	log_debug(NULL, "stuff started, parent is @ %p", ctx);
	sleep(1);
	log_debug(NULL, "stuff done");
	pthread_exit("stuff exited\n");
}

void configuration(logger_t* log)
{
	flash_led(LED1);
	log_init(log, "startup");

	pthread_t self = pthread_self();
	log_debug(log, "config started @ %p", self);

	log_info(NULL, "STUFF THREAD");
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, 256);
	pthread_create(&stuff_thread, &attr, (pf)stuff, self);
	pthread_attr_destroy(&attr);
	sleep(1);

    log_debug(log, "%s v%s", PROJECT_NAME, PROJECT_VERSION);
    log_debug(log, "%s v%s", OPERATING_SYSTEM, KERNEL_VERSION);
    log_debug(log, "platform:%s, device:%s", BOARD, DEVICE);
	sleep(1);

	log_debug(log, "config done");
	pthread_exit("configuration exited\n");
}

void vApplicationIdleHook(void)
{
//    IWDG_ReloadCounter();
}

int main(void)
{
	log_level(LOG_SYSLOG);


	log_info(NULL, "ENTRY");

	dump_task_info(NULL);

	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, 256);
	pthread_create(&config, &attr, (pf)configuration, &log);
	pthread_attr_destroy(&attr);

	log_info(NULL, "CONFIG THREAD");
	dump_task_info(NULL);

	void* status;

	log_info(NULL, "JOIN CONFIG THREAD");
	pthread_join(config, &status);

	printf(status);

	dump_task_info(NULL);

	log_info(NULL, "JOIN STUFF THREAD");
	pthread_join(stuff_thread, &status);

	printf(status);

	log_info(NULL, "EXIT");
	dump_task_info(NULL);

	// must call pthread_exit or loop forever when USE_PTHREADS is set to 1
	pthread_exit(0);
	return 0;
}
  
