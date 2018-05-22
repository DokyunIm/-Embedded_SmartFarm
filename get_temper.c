#include "smartfarm.h"

#define MAXTIMINGS 85
#define FAN	6 // BCM_GPIO 6

int ret_humid, ret_temp;


static int DHTPIN = 7;
//static int DHTPIN = 11;

static int dht22_dat[5] = {0,0,0,0,0};

static uint8_t sizecvt(const int read)
{
  if (read > 255 || read < 0)
  {
    printf("Invalid data from wiringPi library\n");
    exit(EXIT_FAILURE);
  }
  return (uint8_t)read;
}

int read_dht22_dat()
{
  uint8_t laststate = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0, i;

  dht22_dat[0] = dht22_dat[1] = dht22_dat[2] = dht22_dat[3] = dht22_dat[4] = 0;

  pinMode(DHTPIN, OUTPUT);
  digitalWrite(DHTPIN, HIGH);
  delay(10);
  digitalWrite(DHTPIN, LOW);
  delay(18);

  digitalWrite(DHTPIN, HIGH);
  delayMicroseconds(40);

  pinMode(DHTPIN, INPUT);


  for ( i=0; i< MAXTIMINGS; i++) {
    counter = 0;
    while (sizecvt(digitalRead(DHTPIN)) == laststate) {
      counter++;
      delayMicroseconds(1);
      if (counter == 255) {
        break;
      }
    }
    laststate = sizecvt(digitalRead(DHTPIN));

    if (counter == 255) break;

    if ((i >= 4) && (i%2 == 0)) {
      dht22_dat[j/8] <<= 1;
      if (counter > 50)
        dht22_dat[j/8] |= 1;
      j++;
    }
  }

  if ((j >= 40) && (dht22_dat[4] == ((dht22_dat[0] + dht22_dat[1] + dht22_dat[2] + dht22_dat[3]) & 0xFF)) ) {
	float t, h;

	h = (float)dht22_dat[0] * 256 + (float)dht22_dat[1];
	h /= 10;
	t = (float)(dht22_dat[2] & 0x7F)* 256 + (float)dht22_dat[3];
	t /= 10.0;
	if ((dht22_dat[2] & 0x80) != 0)  t *= -1;

	ret_humid = (int)h;
	ret_temp = (int)t;
    return ret_temp;
  }
  else
  {
    return 0;
  }
}

void *get_temper(void *arg)
{
	int received_temp;
	pinMode (FAN, OUTPUT) ;
	while(1){
		while (read_dht22_dat() == 0){
			delay(1000); // wait 1sec to refresh
		}
		received_temp = ret_temp;
		pthread_mutex_lock(&temper_mutex);
		while(light_using == 1){
			printf("wait to store temper data\n");
			pthread_cond_wait(&temper_set, &temper_mutex);
		}
		temper_using=1;
		set_temper_data(received_temp);
		temper_using=0;
		pthread_cond_signal(&temper_get);
		pthread_mutex_unlock(&temper_mutex);
		if(received_temp >= 20){
			if(digitalRead(FAN) != 1){
				pthread_create(&t_fan, NULL, on_fan, NULL);
			}
		}
		printf("Temperature = %d\n", received_temp);
		delay(1000);
	}


}
