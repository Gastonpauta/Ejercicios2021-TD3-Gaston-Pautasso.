#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include "../include/tecla.h"
#include "freertos/semphr.h"

#define led_rojo         GPIO_NUM_32  
#define led_verde        GPIO_NUM_33
#define PULSADOR         GPIO_NUM_25
//#define PERIODO          pdMS_TO_TICKS(100) //Periodo fijo cada 1 segundo
#define delay            pdMS_TO_TICKS(500)
#define T_ESPERA_SEM     pdMS_TO_TICKS(1000) //tiempo de espera de semaforo en ticks

void tarealed( void * pvParameters );
TaskHandle_t xHandle1 = NULL; 
SemaphoreHandle_t semaforo = NULL; //Puntero al semaforo

void app_main(){

config_pulsador(PULSADOR);   //configuramos el pulsador

    //Crear el semáforo (arranca “tomado”)
semaforo = xSemaphoreCreateBinary();
    if(semaforo == NULL)
    {
        printf("No se pudo crear el semaforo\n");
        while(true);
    }
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
/////////////////////////////////////////////
////////////////////////////////////////////
void tarealed( void * pvParameters )
{

   // TickType_t xPeriodicity =  PERIODO;			    // Tarea periodica cada 1 seg
   // TickType_t xLastWakeTime = xTaskGetTickCount(); // Guarda en la variable la cantidad de ticks

    gpio_pad_select_gpio(led_rojo); 
    gpio_pad_select_gpio(led_verde); 
    gpio_set_direction(led_rojo, GPIO_MODE_OUTPUT);
    gpio_set_direction(led_verde, GPIO_MODE_OUTPUT);

while (true){


if( xSemaphoreTake( semaforo ,T_ESPERA_SEM) == pdTRUE )
    {
    gpio_set_level(led_verde, 1);
    vTaskDelay(delay);
    gpio_set_level(led_verde,0);
    }

else{
    gpio_set_level(led_rojo, 1);
    vTaskDelay(delay);
    gpio_set_level(led_rojo,0);
    }
    //vTaskDelay(delay);
}}