#include "smartfarm.h"

#define SPI_CHANNEL 0
#define SPI_SPEED 1000000 //1Mhz
#define MAX 100

int main(int argc, char *argv[]){
	int i = 0;
	printf("smartfarm => main proc start\n");

	signal(SIGINT, (void *)sig_handler);
	light_ptr = 0;
	light_using = 0;
	temper_ptr = 0;
	temper_using = 0;

	if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)
	{
		fprintf(stdout, "wiringPiSPISetup Failed :%s\n", strerror(errno));
		exit(1);
	}

	if(wiringPiSetupGpio() == -1)
	{
		fprintf(stdout, "Unable to start wiringPi :%s\n", strerror(errno));
		exit(1);
	}

	pthread_create(&t_temper, NULL, get_temper, NULL);
	pthread_create(&t_light, NULL, get_light, NULL);
	pthread_create(&t_send_temper, NULL, send_temper, NULL);
	pthread_create(&t_send_light, NULL, send_light, NULL);

	while(1){
		printf("main proc running\n");
		delay(10000);
	}



	return 0;
}

void sig_handler(int signo){
	printf("smartfarm => main proc end\n");


	pthread_cancel(t_light);
	pthread_cancel(t_temper);
	pthread_cancel(t_send_temper);
	pthread_cancel(t_send_light);

	pthread_join(t_light, NULL);
	pthread_join(t_temper, NULL);
	pthread_join(t_send_temper, NULL);
	pthread_join(t_send_light, NULL);
	off_led();
	off_fan();

	exit(0);
}
