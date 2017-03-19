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
#define TEST_INTERRUPT 0
#define TEST_DEVICE 1

disk_interface_t sddisk;

int main(void)
{
	volatile int ret;

	flash_led(LED1);

	log_info(NULL, "init sdcard");
    sdcard_mount(&sddisk, 0);

#if TEST_POLLED
	log_info(NULL, "polled test");

	USART_HANDLE_t usart_p = usart_create_polled(CONSOLE_USART, true, USART_FULLDUPLEX, 115200);

//	assert_true(USART1_HANDLE != USART_INVALID_HANDLE);

    while(1) {
		ret = usart_rx(usart_p);
		usart_tx(usart_p, ret);
	}
#endif

#if TEST_INTERRUPT
	uint8_t buffer[32];
	log_info(NULL, "async test");
	USART_HANDLE_t usart_a = usart_create_async(CONSOLE_USART, true, USART_FULLDUPLEX, 115200, 32);

	assert_true(usart_a != USART_INVALID_HANDLE);

	while(1) {
		ret = usart_get_async(usart_a, buffer, 1, 1000);
		if(ret) {
			usart_put_async(usart_a, (const uint8_t*)buffer, ret);
		}
		else {
			printf("got nothing\n");
		}
	}
#endif

#if TEST_DEVICE
	uint8_t buffer[32];
	log_info(NULL, "/dev file test");

	USART_HANDLE_t usart_d = usart_create_dev("/dev/ttyS0", CONSOLE_USART, USART_FULLDUPLEX, 115200, 32);
	assert_true(usart_d != USART_INVALID_HANDLE);

	int ttys0_fd = open("/dev/ttyS0", O_RDWR);
	while(1) {
		ret = read(ttys0_fd, buffer, 1);
		if(ret) {
			write(ttys0_fd, buffer, ret);
		}
		else {
			printf("got nothing\n");
		}
	}
	close(ttys0_fd);

#endif
    return 0;
}
