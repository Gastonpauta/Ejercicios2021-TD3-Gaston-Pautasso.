#define semaforo_h

#include <stdio.h>
#include "driver/gpio.h"
//
void secuencia_semaforo(int led_rojo,int led_amarillo,int led_verde);
void secuencia_intermitente(int led_rojo,int led_amarillo,int led_verde);