#include "smartfarm.h"

#define CS_MCP3208 8 //GPIO 8
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000 //1Mhz
#define RGBLEDPOWER 19

// spi communication with Rpi and get sensor data

int read_mcp3208_adc(unsigned char adcChannel)
{
	unsigned char buff[3];
	int adcValue = 0;

	buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
	buff[1] = ((adcChannel & 0x07) << 6);
	buff[2] = 0x00;

	digitalWrite(CS_MCP3208, 0);
	wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);

	buff[1] = 0x0f & buff[1];
	adcValue = (buff[1] << 8 ) | buff[2];

	digitalWrite(CS_MCP3208, 1);

	return adcValue;
}

void *get_light(void *arg){

	unsigned char adcChannel_light = 0;

	int adcValue_light = 0;

	float vout_light;
	float vout_oftemp;
	float percentrh = 0;
	float supsiondo = 0;

	pinMode(CS_MCP3208, OUTPUT);
	pinMode(RGBLEDPOWER, OUTPUT);

	while(1)
	{
		adcValue_light = read_mcp3208_adc(adcChannel_light);

		pthread_mutex_lock(&light_mutex);
		while(light_using == 1){
			printf("wait to store light data\n");
			pthread_cond_wait(&light_set, &light_mutex);
		}
		light_using=1;
		set_light_data(adcValue_light);
		light_using=0;
		pthread_cond_signal(&light_get);
		pthread_mutex_unlock(&light_mutex);

		printf("light sensor = %u\n", adcValue_light);
		if(adcValue_light > 3500){
			on_led();
		}
		else{
			off_led();
		}
		delay(1000);
	}
}
