// Autor: Gastón Pautasso
// fecha 29/04/21
  
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <driver/adc.h>
//#include <driver/dac.h>

#define tiempo 500/portTICK_PERIOD_MS 
#define LED_UNO GPIO_NUM_25

void app_main() {

adc1_config_width(ADC_WIDTH_12Bit);
adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_0db);
gpio_pad_select_gpio(LED_UNO);
gpio_set_direction(LED_UNO, GPIO_MODE_OUTPUT);
int valor_pot = 0;


while (1)
{
// leo el canal configurado y lo guardo en una variable entera  que va de 0 a 4095
valor_pot = adc1_get_raw(ADC1_CHANNEL_6);  
//
printf("El valor de al ADC es de  %d \n ", valor_pot );
if (valor_pot >= 2000)
{
   gpio_set_level(LED_UNO,1);
}
else
{   
   gpio_set_level(LED_UNO,0); 
}
//
vTaskDelay(tiempo);
}

}