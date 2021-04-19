// Autor: Gastón Pautasso
// fecha 13/04/21
#include "../driver/include/driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//
//
#define T_ON		200/portTICK_PERIOD_MS
#define LED_UNO GPIO_NUM_32 
#define LED_DOS GPIO_NUM_33 
#define LED_TRES GPIO_NUM_25 
#define PULSADOR_UNO GPIO_NUM_26 
#define PULSADOR_DOS GPIO_NUM_27 
void  sec_derecha ();
void  sec_izquierda();
int k=0;
void app_main(){
//
// selecciono un pad I/O del multiplexor (gpio)
	gpio_pad_select_gpio(LED_UNO);
	gpio_pad_select_gpio(LED_DOS);
	gpio_pad_select_gpio(LED_TRES);
	gpio_pad_select_gpio(PULSADOR_UNO);
	gpio_pad_select_gpio(PULSADOR_DOS);
//
//configuro el pad como salida o entrada 
// Para el caso de los led, Salidas. Para los pulsadores, Entrada.
	gpio_set_direction(LED_UNO, GPIO_MODE_OUTPUT);
	gpio_set_direction(LED_DOS, GPIO_MODE_OUTPUT);
	gpio_set_direction(LED_TRES, GPIO_MODE_OUTPUT);
    gpio_set_direction(PULSADOR_UNO, GPIO_MODE_INPUT);
    gpio_set_direction(PULSADOR_DOS, GPIO_MODE_INPUT);

// activo las resistencias pulldown de los pulsadores
gpio_set_pull_mode(PULSADOR_UNO, GPIO_PULLDOWN_ONLY);
gpio_set_pull_mode(PULSADOR_DOS, GPIO_PULLDOWN_ONLY);

//gpio_get_level(PULSADOR1) -> GPIO obtiene el nivel de entrada. 
// Si el pad no está configurado para entrada (o entrada y salida), el valor devuelto es siempre 0.
while (1){

	if (k==0){
        k++ ;
		sec_derecha();
	}
	else{
	    sec_izquierda();
	}
	}
    }
//funcion secuencia derecha (se mantiene funcionando hasta que se active el pulsador_dos)
void sec_derecha(){
while (gpio_get_level(PULSADOR_DOS) == 0){

            gpio_set_level(LED_UNO,1);
			gpio_set_level(LED_DOS,0);
			gpio_set_level(LED_TRES,0);
			vTaskDelay(T_ON);
//
            gpio_set_level(LED_UNO,0);
			gpio_set_level(LED_DOS,1);
			gpio_set_level(LED_TRES,0);
			vTaskDelay(T_ON);
//
            gpio_set_level(LED_UNO, 0);
			gpio_set_level(LED_DOS, 0);
			gpio_set_level(LED_TRES,1);
			vTaskDelay(T_ON);
			}
			}

//funcion secuencia izquierda
void sec_izquierda(){
	k--;
while (gpio_get_level(PULSADOR_UNO) == 0){

            gpio_set_level(LED_UNO, 0);
			gpio_set_level(LED_DOS, 0);
			gpio_set_level(LED_TRES,1);
			vTaskDelay(T_ON);
            gpio_set_level(LED_UNO, 0);
			gpio_set_level(LED_DOS, 1);
			gpio_set_level(LED_TRES, 0);
			vTaskDelay(T_ON);
            gpio_set_level(LED_UNO, 1);
			gpio_set_level(LED_DOS, 0);
			gpio_set_level(LED_TRES, 0);
			vTaskDelay(T_ON);
			}
			}