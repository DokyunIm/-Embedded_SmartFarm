#include "smartfarm.h"

//#define RGBLEDPOWER  24
#define RGBLEDPOWER 19

void on_led()
{
	digitalWrite(RGBLEDPOWER, 1);
}

void off_led()
{
	digitalWrite(RGBLEDPOWER, 0); //Off
}

