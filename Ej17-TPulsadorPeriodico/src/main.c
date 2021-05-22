#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include "../include/tecla.h"


#define led         GPIO_NUM_32  
#define PULSADOR    GPIO_NUM_25
#define PERIODO     pdMS_TO_TICKS(1000) //Periodo fijo cada 1 segundo

static TickType_t k ;
static TickType_t delay;

void tarealed( void * pvParameters );
TaskHandle_t xHandle1 = NULL; 

void app_main(){

config_pulsador(PULSADOR);   //configuramos el pulsador

         xTaskCreatePinnedToCore( 

                  tarealed,                  //Función que implementa la tarea. La misma no debe retornar.
                 "Tarea led",                //Nombre que reprenta la tarea, para facilitar la depuración.
                 configMINIMAL_STACK_SIZE,   //Tamaño del stack en bytes
                 NULL,                       //Puntero que se utilizará como parámetro para la tarea que se está creando. Como no lo usamos ponemos NULL
                 tskIDLE_PRIORITY+1,         //Prioridad de la tarea
                 &xHandle1,                  //Puntero a la tarea
                 0                           //Procesador donde se ejecuta la tarea
                );
         configASSERT( xHandle1 );  

 if( xHandle1 == NULL )
        {
            vTaskDelete( xHandle1 );
        }
        
}
void tarealed( void * pvParameters )
{

    TickType_t xPeriodicity =  PERIODO;			    // Tarea periodica cada 1 seg
    TickType_t xLastWakeTime = xTaskGetTickCount(); // Guarda en la variable la cantidad de ticks

    gpio_pad_select_gpio(led); 
    gpio_set_direction(led, GPIO_MODE_OUTPUT);

while (true){

k = tiempocontado() ;

//comprobamos que el tiempo de pulsado es menor al periodo
if(k < PERIODO )
     {
       //le asignamos a la variable delay la cantidad de ticks mientras el pulsador estuvo presionado  
        delay = tiempocontado();
     }
//  
    gpio_set_level(led, 1);
    vTaskDelay(delay);
    gpio_set_level(led,0);

    vTaskDelayUntil( &xLastWakeTime , xPeriodicity ); //espera a que el tiempo del periodo se cumpla
}}