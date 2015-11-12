
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "leds.h"
#include "heap_ccram.h"

#define LOOPS 5           // times to repeat the same allocation cycle
#define HEAP_BLOCK_SIZE 8 // copied from heap_ccram.c
#define MAXBLOCKS 2048    // just make sure we have enough spaces in memarray to store all allocated addresses
#define SIZE 128          // allocation request size

void* memarray[MAXBLOCKS]; // a place to store allocation addresses

// tries to allocate as many blocks as will fit in the heap (that implied by the alloc and freee functions
void test_malloc_free(const char* name, void*(*alloc)(size_t), void(*freee)(void*), size_t freespace)
{
    printf("starting %s test...\n", name);
    printf("free space: %u\n", freespace);
    char cycle = 0;
    unsigned long blocks = 0;

    while(cycle++ < LOOPS)
    {
        blocks = 0;
        memarray[blocks] = alloc(SIZE);

        while(memarray[blocks] && blocks < MAXBLOCKS-1)
        {
            blocks++;
            memarray[blocks] = alloc(SIZE);
        }

        printf("allocated %u blocks, %dbytes, actual %dbytes\n", blocks, blocks * SIZE, blocks * (SIZE + HEAP_BLOCK_SIZE));

        while(blocks)
        {
            blocks--;
            freee(memarray[blocks]);
        }
    }
}


int main(void)
{
    // use the system led flasher to flash one of the leds
    flash_led(LED1);

    printf("test memory allocation in ccram and normal ram\n");

    int loop = 0;
	for(;;)
	{
		printf("test loop %d\n", loop++);
		test_malloc_free("main", malloc, free, xPortGetFreeHeapSize());
		test_malloc_free("ccram", malloc_ccram, free_ccram, xPortGetFreeHeapSize_ccram());
		toggle_led(LED2);
		usleep(250000);
	}

	pthread_exit(0);
    // should never get here
    return 0;
}
