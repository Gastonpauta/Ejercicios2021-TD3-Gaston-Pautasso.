#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include "../include/tecla.h"
#include "../include/led.h"

#define PULSADOR    GPIO_NUM_25


void app_main(){

config_pulsador(PULSADOR);   //configuramos el pulsador

}
