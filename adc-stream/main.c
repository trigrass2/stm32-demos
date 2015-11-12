
#include <unistd.h>
#include <pthread.h>

#include "leds.h"
#include "adc_stream.h"

/********************
 *
 * demo is broken :(
 *
 ********************/

void adc_stream_callback(unsigned_stream_type_t* buffer, uint16_t length, uint8_t channels, stream_connection_t* conn)
{
    const char* appdata = (const char*)conn->ctx;
    printf("%s: %d %x %d %d %d (%s)\n", conn->name, *buffer, buffer, length, channels, conn->stream_channel, appdata);
}

stream_connection_t adc_stream_conn;


int main(void)
{
    // use the system led flasher to flash one of the leds
    flash_led(LED1);

    adc_stream_init();
	adc_stream_start();

	adc_stream_set_samplerate(2000);

	stream_connection_init(&adc_stream_conn, adc_stream_callback, "adc process", "some app context data");
	adc_stream_connect_service(&adc_stream_conn, 0);

	for(;;)
	{
		toggle_led(LED2);
		stream_connection_enable(&adc_stream_conn, true);
		sleep(1);
		stream_connection_enable(&adc_stream_conn, false);
		sleep(1);
	}

	pthread_exit(0);
    return 0;
}
