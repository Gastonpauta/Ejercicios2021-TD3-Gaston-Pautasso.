#ifndef LED_H 
#define LED_H

#include "driver/gpio.h" 

void configLed(int rojo, int amarillo, int verde);

void secuencia(char k);

#endif