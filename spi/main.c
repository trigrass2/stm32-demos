#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "leds.h"
#include "spi.h"

#define TEST_POLLED 0
#define TEST_INTERRUPT 0
#define TEST_DEVICE 1

int main(void)
{
	flash_led(LED1);

#if TEST_POLLED
	uint8_t byte = 0x42;
	SPI_HANDLE_t spih1 = spi_create_polled(SPI1, true, SPI_FIRSTBIT_MSB, SPI_PHASE_1EDGE, SPI_POLARITY_LOW, 10000000, SPI_DATASIZE_8BIT);
	SPI_HANDLE_t spih2 = spi_create_polled(SPI2, true, SPI_FIRSTBIT_MSB, SPI_PHASE_1EDGE, SPI_POLARITY_LOW, 5000000, SPI_DATASIZE_8BIT);
	SPI_HANDLE_t spih3 = spi_create_polled(SPI3, true, SPI_FIRSTBIT_MSB, SPI_PHASE_1EDGE, SPI_POLARITY_LOW, 1000000, SPI_DATASIZE_8BIT);

    while(1) {
    	spi_clear_ss(spih1);
		byte = spi_transfer_polled(spih1, byte);
    	spi_set_ss(spih1);
    	spi_clear_ss(spih2);
		byte = spi_transfer_polled(spih2, byte);
    	spi_set_ss(spih2);
    	spi_clear_ss(spih3);
		byte = spi_transfer_polled(spih3, byte);
    	spi_set_ss(spih3);
		printf("%d", byte);
		sleep(1);
	}
#endif

#if TEST_INTERRUPT
    uint8_t byte;
    uint8_t count = 0;
	uint8_t buffer[32];
	SPI_HANDLE_t spih1 = spi_create_async(SPI1, true, SPI_FIRSTBIT_MSB, SPI_PHASE_1EDGE, SPI_POLARITY_LOW, SPI_DATASIZE_8BIT, 10000000, 32);
	SPI_HANDLE_t spih2 = spi_create_async(SPI2, true, SPI_FIRSTBIT_MSB, SPI_PHASE_1EDGE, SPI_POLARITY_LOW, SPI_DATASIZE_8BIT, 5000000, 32);
	SPI_HANDLE_t spih3 = spi_create_async(SPI3, true, SPI_FIRSTBIT_MSB, SPI_PHASE_1EDGE, SPI_POLARITY_LOW, SPI_DATASIZE_8BIT, 5000000, 32);


	while(1) {
		memset((char*)buffer, 0, sizeof(buffer));
		spi_clear_ss(spih1);
		byte = spi_put_async(spih1, (const uint8_t*)"12345", 5);
		count = 0;
		while(count < byte) {
			count += spi_get_async(spih1, buffer, 5, 1000);
		}
		spi_set_ss(spih1);


		memset((char*)buffer, 0, sizeof(buffer));
		spi_clear_ss(spih2);
		byte = spi_put_async(spih2, (const uint8_t*)"12345", 5);
		count = 0;
		while(count < 5) {
			count += spi_get_async(spih2, buffer, 5, 1000);
		}
		spi_set_ss(spih2);

		memset((char*)buffer, 0, sizeof(buffer));
		spi_clear_ss(spih3);
		byte = spi_put_async(spih3, (const uint8_t*)"12345", 5);
		count = 0;
		while(count < 5) {
			count += spi_get_async(spih3, buffer, 5, 1000);
		}
		spi_set_ss(spih3);

		sleep(1);
	}
#endif

#if TEST_DEVICE
	uint8_t buffer[32];

	SPI_HANDLE_t spih1 = spi_create_dev("/dev/ttyS0", SPI1, true, SPI_FIRSTBIT_MSB, SPI_PHASE_1EDGE, SPI_POLARITY_LOW, SPI_DATASIZE_8BIT, 10000000, 32);

	int ret;

	while(1) {
		int ttys0_fd = open("/dev/ttyS0", O_RDWR);
		memset((char*)buffer, 0, sizeof(buffer));

		spi_clear_ss(spih1);
		ret = write(ttys0_fd, "12345", 5);
		if(ret > 0) {
			ret = read(ttys0_fd, (char*)buffer, 5);
		}
		spi_set_ss(spih1);
		close(ttys0_fd);

		sleep(1);
	}

#endif
    return 0;
}
