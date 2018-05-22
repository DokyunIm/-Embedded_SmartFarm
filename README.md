## Smart Farm in Cloud - 2018 Embedded System
  
### Details
  - smartfarm.h
    + Header File
  
  - smartfarm.c
    + main function
    + create other threads
    + interrupt handling (when program terminated,  cancel(exit) threads and turn off module)
    
  - get_light.c
    + get analogous data for lightness sensor
    + save data and time into buffer
    + if sensor value is above 3500, turn on led
    
  - get_temper.c
    + get temperature data for sensor
    + save data and time into buffer
    + if temperature goes beyond 20 degrees, turn on Fan for 5 second
    
  - control_fan.c
    + turn on and off fan
    
  - control_led.c
    + turn on and off led
    
  - save_data.c
    + store data(lightness value, temperature, time) in buffer
    
  - send_data.c
    + store data in remote database server(NCP) 

***
### Demonstration video
  -  <>
    
    
