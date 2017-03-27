#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "leds.h"
#include "onewire.h"
#include "pthread.h"


int main(void)
{
	uint64_t ids[1];

	flash_led(LED1);

	USART_HANDLE_t ow = onewire_create(USART2);
	printf("onewire create: %d\n", ow);

	printf("onewire reset: %s\n", onewire_reset(ow) ? "success" : "failed");

	onewire_search_ids(ow, ids, 1);

	printf("found: %08X%08X\n", *((uint32_t*)ids), *(((uint32_t*)ids)+1));

	pthread_exit(NULL);

    return 0;
}
