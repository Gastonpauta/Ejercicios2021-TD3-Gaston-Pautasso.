#include "../include/led.h"
#include "driver/gpio.h" 

static int led1 ;
static int led2 ;
static int led3 ;
void configLed(int rojo, int amarillo, int verde){

led1 = rojo ;
led2 = amarillo ;
led3 = verde;
gpio_pad_select_gpio(rojo);
gpio_pad_select_gpio(amarillo);
gpio_pad_select_gpio(verde);

gpio_set_direction(rojo, GPIO_MODE_OUTPUT);
gpio_set_direction(amarillo, GPIO_MODE_OUTPUT);
gpio_set_direction(verde, GPIO_MODE_OUTPUT);
}

void secuencia(char k){

    if(k =='R'){

        gpio_set_level(led1, 1);
        gpio_set_level(led2, 0);
        gpio_set_level(led3, 0);
}
    if(k=='A'){
        
        gpio_set_level(led1, 0);
        gpio_set_level(led2, 1);
        gpio_set_level(led3, 0);
}
    if(k=='V'){
        
        gpio_set_level(led1, 0);
        gpio_set_level(led2, 0);
        gpio_set_level(led3, 1);
}
    if(k=='I'){
 
        gpio_set_level(led1, 0);
        gpio_set_level(led2, 1);
        gpio_set_level(led3, 0);
}
    if(k=='O'){
 
        gpio_set_level(led1, 0);
        gpio_set_level(led2, 0);
        gpio_set_level(led3, 0);
}
}