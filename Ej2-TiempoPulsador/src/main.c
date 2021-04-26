// Autor: Gastón Pautasso
// fecha 26/04/21
#include "../driver/include/driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//
//
#define T_ON		100/portTICK_PERIOD_MS
#define LED_UNO GPIO_NUM_32 
#define LED_DOS GPIO_NUM_33 
#define LED_TRES GPIO_NUM_25 
#define PULSADOR_UNO GPIO_NUM_26 
#define PULSADOR_DOS GPIO_NUM_27 
#define PULSADOR_TRES GPIO_NUM_14

int k=0;
int i=0;
int j=0;
void app_main(){
//
// selecciono un pad I/O del multiplexor (gpio)
	gpio_pad_select_gpio(LED_UNO);
	gpio_pad_select_gpio(LED_DOS);
	gpio_pad_select_gpio(LED_TRES);
	gpio_pad_select_gpio(PULSADOR_UNO);
	gpio_pad_select_gpio(PULSADOR_DOS);
    gpio_pad_select_gpio(PULSADOR_TRES);
//
//configuro el pad como salida o entrada 
// Para el caso de los led, Salidas. Para los pulsadores, Entrada.
	gpio_set_direction(LED_UNO, GPIO_MODE_OUTPUT);
	gpio_set_direction(LED_DOS, GPIO_MODE_OUTPUT);
	gpio_set_direction(LED_TRES, GPIO_MODE_OUTPUT);
    gpio_set_direction(PULSADOR_UNO, GPIO_MODE_INPUT);
    gpio_set_direction(PULSADOR_DOS, GPIO_MODE_INPUT);
    gpio_set_direction(PULSADOR_TRES, GPIO_MODE_INPUT);

// activo las resistencias pulldown de los pulsadores
    gpio_set_pull_mode(PULSADOR_UNO, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(PULSADOR_DOS, GPIO_PULLDOWN_ONLY); 
    gpio_set_pull_mode(PULSADOR_TRES, GPIO_PULLDOWN_ONLY);

//gpio_get_level(PULSADOR1) -> GPIO obtiene el nivel de entrada. 
// Si el pad no está configurado para entrada (o entrada y salida), el valor devuelto es siempre 0.

while (1){
//	 
	if (gpio_get_level(PULSADOR_UNO) == 1 ){
        k = k+1 ;}
//
	    else if(( gpio_get_level(PULSADOR_UNO) == 0) ){

		        if(k>1){
					 gpio_set_level(LED_UNO,1);
					 k--;}
//
				else{gpio_set_level(LED_UNO,0);}}
//
    if(gpio_get_level(PULSADOR_DOS) == 1 ){
       i= i+1 ;}
//
        else if(( gpio_get_level(PULSADOR_DOS) == 0) ){
				if(i>1){
					 gpio_set_level(LED_DOS,1);
					 i--;} 
			    else{gpio_set_level(LED_DOS,0);}}
//
    if(gpio_get_level(PULSADOR_TRES) == 1 ){
       j= j+1 ;}
//
        else if(( gpio_get_level(PULSADOR_TRES) == 0) ){
				if(j>1){
					 gpio_set_level(LED_TRES,1);
					 j--;} 
				else{gpio_set_level(LED_TRES,0);}}
//
//
//
	vTaskDelay(T_ON);
		}
		}