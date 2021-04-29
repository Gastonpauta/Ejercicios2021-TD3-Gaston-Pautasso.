// Autor: Gastón Pautasso
// fecha 29/04/21
  
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <driver/adc.h>
#include <driver/dac.h>

#define tiempo 500/portTICK_PERIOD_MS 
#define LED_UNO GPIO_NUM_33

void app_main() {

adc1_config_width(ADC_WIDTH_12Bit);
adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_0db);
dac_output_enable(DAC_CHANNEL_1);
gpio_pad_select_gpio(LED_UNO);
gpio_set_direction(LED_UNO, GPIO_MODE_OUTPUT);
int valor_pot = 0;
int valor_dac = 0 ;

while (1)
{
// leo el canal configurado y lo guardo en una variable entera  que va de 0 a 4095
valor_pot = adc1_get_raw(ADC1_CHANNEL_6);  
printf("El valor de al ADC es de  %d \n ", valor_pot );// imprime en el puerto serie el valor del ADC
valor_dac = valor_pot ;
dac_output_voltage(DAC_CHANNEL_1 ,(valor_dac*255)/4095); //define un señal analogica de 0 a 3.1 V en el pad 25 correspondiente al canal 1 del dac

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