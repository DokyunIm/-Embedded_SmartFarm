#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <stdint.h>
#include <errno.h>
#include <mysql/mysql.h>
#include <time.h>
#include <math.h>
#include <signal.h>
#include <stdint.h>

#define BUFMAX 50

pthread_t t_light, t_temper, t_fan;

pthread_t t_send_light;
pthread_cond_t light_set, light_get;
pthread_mutex_t light_mutex;
int light_data_buffer[BUFMAX];
char light_timestamp_buffer[BUFMAX][20];
int light_ptr;
int light_using;

pthread_t t_send_temper;
pthread_cond_t temper_set, temper_get;
pthread_mutex_t temper_mutex;
int temper_data_buffer[BUFMAX];
char temper_timestamp_buffer[BUFMAX][20];
int temper_ptr;
int temper_using;

// smartfarm.c
void sig_handler(int signo);


// get_temper.c
void *get_temper(void *arg);
static uint8_t sizecvt(const int read);
int read_dht22_dat();


// get_light.c
void *get_light(void *arg);
int read_mcp3208_adc(unsigned char adcChannel);


// control_led.c
void on_led();
void off_led();


// control_fan.c
void *on_fan(void *arg);
void off_fan();

// save_data.c
void set_light_data(int value);
void set_temper_data(int value);



// send_data.c
void *send_light(void *arg);
void *send_temper(void *arg);

