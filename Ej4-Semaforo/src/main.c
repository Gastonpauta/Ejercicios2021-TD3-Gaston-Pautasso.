// Autor: Gastón Pautasso
// fecha 29/04/21
  
#include "stdio.h"
#include "stdio.h"
#include "../include/led.h"
#include "../include/tecla.h"
#include "../include/semaforo.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define tiempo 500/portTICK_PERIOD_MS
#define led_rojo GPIO_NUM_26
#define led_verde GPIO_NUM_33
#define led_amarillo GPIO_NUM_32
#define PULSADOR GPIO_NUM_25

void app_main(){

configuracion_leds(led_rojo, led_amarillo, led_verde);
config_pulsador(PULSADOR);
    
while(1){

if (gpio_get_level(PULSADOR)==1)
{
    secuencia_semaforo(led_rojo, led_amarillo, led_verde);
}
else{
secuencia_intermitente(led_rojo,led_amarillo,led_verde) ;
}
vTaskDelay(tiempo);
}
}
