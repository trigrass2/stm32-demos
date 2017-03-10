#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "asserts.h"
#include "leds.h"
#include "usart.h"
#include "sdcard_diskio.h"
#include "logger.h"

#define TEST_POLLED 0
#define TEST_INTERRUPT 1
#define TEST_DEVICE 0

disk_interface_t sddisk;

int main(void)
{

	flash_led(LED1);

	log_info(NULL, "init sdcard");
    sdcard_mount(&sddisk, 0);

#if TEST_POLLED
	log_info(NULL, "polled test");
	USART_HANDLE_t usart_p = usart_create_polled(USART2, true, USART_FULLDUPLEX, 115200);

	assert_true(usart_p != USART_INVALID_HANDLE);

    while(1) {
		usart_tx(usart_p, byte);
		byte = usart_rx(usart_p);
		printf("received %d\n", byte);
		sleep(1);
	}
#endif

#if TEST_INTERRUPT
	uint8_t buffer[32];
    uint8_t count = 0;
	log_info(NULL, "async test");
	USART_HANDLE_t usart_a = usart_create_async(USART2, true, USART_FULLDUPLEX, 115200, 5);

	assert_true(usart_a != USART_INVALID_HANDLE);

	while(1) {
		memset((char*)buffer, 0, sizeof(buffer));

		count = usart_put_async(usart_a, (const uint8_t*)"12345", 5);
		memset((char*)buffer, 0, sizeof(buffer));
		count = usart_get_async(usart_a, buffer, 10, 1000);

		if(count < 32)
			buffer[count] = 0;

		printf("received: %d, %s\n", count, buffer);

		sleep(1);
	}
#endif

#if TEST_DEVICE
	uint8_t buffer[32];
    uint8_t count = 0;
	log_info(NULL, "/dev file test");

	USART_HANDLE_t usart_d = usart_create_dev("/dev/ttyS0", USART2, true, USART_FULLDUPLEX, 115200, 32);

	assert_true(usart_d != USART_INVALID_HANDLE);

	int ret;

	while(1) {
		int ttys0_fd = open("/dev/ttyS0", O_RDWR);
		memset((char*)buffer, 0, sizeof(buffer));

		ret = write(ttys0_fd, "12345", 5);
		ret = read(ttys0_fd, (char*)buffer, 5);

		if(ret >= 0) {
			buffer[ret] = 0;
		}

		close(ttys0_fd);

		printf("received: %d, %s\n", ret, buffer);

		sleep(1);
	}

#endif
    return 0;
}
