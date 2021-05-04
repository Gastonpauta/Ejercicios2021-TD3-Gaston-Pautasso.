#include "../include/tecla.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void config_pulsador(int PULSADOR){
gpio_pad_select_gpio(PULSADOR);
gpio_set_direction(PULSADOR, GPIO_MODE_INPUT);
gpio_set_pull_mode(PULSADOR, GPIO_PULLDOWN_ONLY);
}