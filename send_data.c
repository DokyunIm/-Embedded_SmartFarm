#include "smartfarm.h"

#define DBHOST ""
#define DBUSER ""
#define DBPASS ""
#define DBNAME ""


void *send_light(void *arg){
	MYSQL *connector;
	MYSQL_RES *result;
	MYSQL_ROW row;
	int i = 0;
	int count = 0;
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	sleep(10);
	while(1){
		pthread_mutex_lock(&light_mutex);
		while(light_using == 1){
			pthread_cond_wait(&light_get, &light_mutex);
		}
		light_using=1;
		if(light_ptr != 0){
			connector = mysql_init(NULL);
			if (!mysql_real_connect(connector, DBHOST, DBUSER, DBPASS, DBNAME, 3306, NULL, 0))
			{
				fprintf(stderr, "%s\n", mysql_error(connector));
				exit(1);
			}
			char query[2048];
			for(i =0; i < light_ptr; i ++){
				sprintf(query,"insert into light_data(data, regdate) values(%d, %s)", light_data_buffer[i], light_timestamp_buffer[i]);
				//printf("%s\n", query);
				if(mysql_query(connector, query))
				{
					fprintf(stderr, "%s\n", mysql_error(connector));
					printf("Write DB error\n");
				}
			}
			mysql_close(connector);
			pthread_testcancel();
			light_ptr=0;
		}
		light_using=0;
		pthread_cond_signal(&light_set);
		pthread_mutex_unlock(&light_mutex);
		sleep(10);
	}
}


void *send_temper(void *arg){
	MYSQL *connector;
	MYSQL_RES *result;
	MYSQL_ROW row;
	int i = 0;
	int count = 0;
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	sleep(10);
	while(1){
		pthread_mutex_lock(&temper_mutex);
		while(temper_using == 1){
			pthread_cond_wait(&temper_get, &temper_mutex);
		}
		temper_using=1;
		if(temper_ptr != 0){
			connector = mysql_init(NULL);
			if (!mysql_real_connect(connector, DBHOST, DBUSER, DBPASS, DBNAME, 3306, NULL, 0))
			{
				fprintf(stderr, "%s\n", mysql_error(connector));
				exit(1);
			}
			char query[2048];
			for(i =0; i < temper_ptr; i ++){
				sprintf(query,"insert into temper_data(data, regdate) values(%d, %s)", temper_data_buffer[i], temper_timestamp_buffer[i]);
				//printf("%s\n", query);
				if(mysql_query(connector, query))
				{
					fprintf(stderr, "%s\n", mysql_error(connector));
					printf("Write DB error\n");
				}
			}
			mysql_close(connector);
			pthread_testcancel();
			temper_ptr=0;
		}
		temper_using=0;
		pthread_cond_signal(&temper_set);
		pthread_mutex_unlock(&temper_mutex);
		sleep(10);
	}
}

