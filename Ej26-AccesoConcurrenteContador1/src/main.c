#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include "pulsador.h"


extern int contador ;
//#define PERIODO     pdMS_TO_TICKS(100) //Periodo fijo cada 1 segundo
#define led         GPIO_NUM_32  

void tarealed( void* taskParmPtr );

void app_main(){

    inicializarPulsador();

        BaseType_t res = xTaskCreatePinnedToCore( 

                  tarealed,                  //Función que implementa la tarea. La misma no debe retornar.
                 "Tarea led",                //Nombre que reprenta la tarea, para facilitar la depuración.
                 configMINIMAL_STACK_SIZE*2,   //Tamaño del stack en bytes
                 NULL,                       //Puntero que se utilizará como parámetro para la tarea que se está creando. Como no lo usamos ponemos NULL
                 tskIDLE_PRIORITY,         //Prioridad de la tarea
                 NULL,                 //Puntero a la tarea
                 1                           //Procesador donde se ejecuta la tarea
                );

 // Gestion de errores
	if(res == pdFAIL)
	{
		printf( "Error al crear la tarea.\r\n" );
		while(true);					// si no pudo crear la tarea queda en un bucle infinito
	}
}
void tarealed( void * pvParameters )
{

    TickType_t xPeriodicity ;	
    TickType_t delay ;		   
    TickType_t xLastWakeTime = xTaskGetTickCount(); // Guarda en la variable la cantidad de ticks
    TickType_t PERIODO ;
    gpio_pad_select_gpio(led); 
    gpio_set_direction(led, GPIO_MODE_OUTPUT);

while (true){
     
    PERIODO =  pdMS_TO_TICKS(contador);
    xPeriodicity = PERIODO ;
    delay= PERIODO / 2;

    gpio_set_level(led, 1);
    vTaskDelay(delay);
    gpio_set_level(led,0);

    vTaskDelayUntil( &xLastWakeTime , xPeriodicity ); //espera a que el tiempo del periodo se cumpla
}}