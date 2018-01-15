
#include <unistd.h>
#include <pthread.h>

#include "leds.h"

#include "adc_stream.h"


void adc_stream_callback(unsigned_stream_type_t* buffer, uint16_t length, uint8_t channels, stream_connection_t* conn)
{
    const char* appdata = (const char*)conn->ctx;

    /**
     * sample data is available in the buffer, adc channel data is interleaved by channel number
     */

    printf("%s: sample-value=%d@%p length=%d sample-channels=%d client-channel=%d appdata=(%s)\n", conn->name, *buffer, buffer, length, channels, conn->stream_channel, appdata);
}

//// prints all samples
//// use unsigned_stream_type_t or signed_stream_type_t as needed.
//void adc_stream_callback(unsigned_stream_type_t* buffer, uint16_t length, uint8_t channels, stream_connection_t* conn)
//{
//	uint32_t sample;
//	uint32_t channel;
//
//   	for (sample = 0; sample < length; sample += channels) {
//   		for (channel = 0; channel < channels; channel++) {
//   			prinf("sample %d channel %d value %d\n", sample, channel, buffer[sample + channel]);
//		}
//   	}
//}

int main(void)
{
    // use the system led flasher to flash one of the leds
    flash_led(LED1);

    // start stream service
    adc_stream_init();
	adc_stream_start();
	adc_stream_set_samplerate(4000);

	// start stream, client
	stream_connection_t adc_stream_conn;
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
