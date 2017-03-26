
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "leds.h"
#include "logger.h"
#include "vfifo.h"

int main(void)
{
	logger_t tl;
	log_init(&tl, "test");

	flash_led(LED1);
	vfifo_t* f1 =  vfifo_create(320);
	vfifo_t* f2 =  vfifo_create(320);

	assert_true(f1);
	assert_true(f2);

	int got = 1;
	int put = 1;
	int n;
	int r;
	int mod = 13;
	srand(mod);

	char buf[512];

	for(uint8_t i = 0; i < 100; i++) {
		log_debug(&tl, "put block test");

		n = 0;
		while(!vfifo_full(f1)) {
			r = rand() % mod;
			put = vfifo_put_block(f1, "0123456789", r);
			n += put;

	//		log_info(&tl, "put=%d/%d, sum=%d, size=%d, free=%d, used=%d, full=%d", put, r, n,
	//						vfifo_number_of_slots(f1), vfifo_free_slots(f1), vfifo_used_slots(f1), vfifo_full(f1));
		}

		assert_true(vfifo_free_slots(f1) == 0);
		assert_true(vfifo_used_slots(f1) == 320);

		log_debug(&tl, "get block test");
		n = 0;
		while(!vfifo_empty(f1)) {
			r = rand() % mod;
			got = vfifo_get_block(f1, buf, r);
			n += got;

	//		log_info(&tl, "got=%d/%d, sum=%d, size=%d, free=%d, used=%d, empty=%d", got, r, n,
	//						vfifo_number_of_slots(f1), vfifo_free_slots(f1), vfifo_used_slots(f1), vfifo_empty(f1));
		}

		assert_true(vfifo_free_slots(f1) == 320);
		assert_true(vfifo_used_slots(f1) == 0);
	}

	vfifo_delete(f1);
	vfifo_delete(f2);

	while(1);

	return 0;
}
