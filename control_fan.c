#include "smartfarm.h"

#define FAN	6 // BCM_GPIO 6

void *on_fan(void *arg){
	digitalWrite (FAN, 1) ; // On
	delay(5000);
	digitalWrite(FAN, 0);
}

void off_fan(){
	digitalWrite(FAN, 0);
}

