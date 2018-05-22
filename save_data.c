#include "smartfarm.h"



void set_light_data(int value){
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer);
	light_data_buffer[light_ptr] = value;
	sprintf(light_timestamp_buffer[light_ptr], "%04d%02d%02d%02d%02d%02d",
				t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
				t->tm_hour, t->tm_min, t->tm_sec);
	light_ptr++;
	return;
}

void set_temper_data(int value){
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer);
	temper_data_buffer[temper_ptr] = value;
	sprintf(temper_timestamp_buffer[temper_ptr], "%04d%02d%02d%02d%02d%02d",
				t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
				t->tm_hour, t->tm_min, t->tm_sec);
	temper_ptr++;
	return;
}
