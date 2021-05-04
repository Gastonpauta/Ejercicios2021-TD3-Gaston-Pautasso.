#include "../include/led.h"
#include "driver/gpio.h"


void configuracion_leds (int led_rojo,int led_amarillo ,int led_verde ){


gpio_pad_select_gpio(led_rojo);
gpio_pad_select_gpio(led_amarillo);
gpio_pad_select_gpio(led_verde);

gpio_set_direction(led_rojo, GPIO_MODE_OUTPUT);
gpio_set_direction(led_amarillo, GPIO_MODE_OUTPUT);
gpio_set_direction(led_verde, GPIO_MODE_OUTPUT);
}