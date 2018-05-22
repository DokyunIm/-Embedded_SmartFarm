smartfarm: smartfarm.o get_light.o get_temper.o control_led.o control_fan.o save_data.o send_data.o
	gcc -o smartfarm smartfarm.o get_light.o get_temper.o control_led.o control_fan.o save_data.o send_data.o -lwiringPi -pthread -lmysqlclient

smartfarm.o: smartfarm.c
	gcc -O -c smartfarm.c
	
get_light.o: get_light.c
	gcc -O -c get_light.c
	
get_temper.o: get_temper.c
	gcc -O -c get_temper.c
	
control_led.o: control_led.c
	gcc -O -c control_led.c

control_fan.o: control_fan.c
	gcc -O -c control_fan.c
	
save_data.o: save_data.c
	gcc -O -c save_data.c
	
send_data.o: send_data.c
	gcc -O -c send_data.c
	
debug:
	gcc -g -o debug_smartfarm smartfarm.c get_light.c get_temper.c control_led.c control_fan.c save_data.c send_data.c -lwiringPi -pthread -lmysqlclient
	
clean:
	rm -f smartfarm.o get_light.o get_temper.o control_led.o control_fan.o save_data.o send_data.o smartfarm debug_smartfarm