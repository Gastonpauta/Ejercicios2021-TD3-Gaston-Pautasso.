#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include "pulsador.h"

#define SALIDA1     GPIO_NUM_25
#define PERIODO_MS  1000
#define PERIODO     pdMS_TO_TICKS(PERIODO_MS)



gpio_int_type_t led [N_PULSADOR] = {GPIO_NUM_25, GPIO_NUM_33};

void tarealed( void* taskParmPtr ); //Prototipo de la función de la tarea

void app_main()
{
    inicializarPulsador();

    BaseType_t res = xTaskCreatePinnedToCore(
            tarealed,                     	// Funcion de la tarea a ejecutar
            "tarealed",   	                // Nombre de la tarea como String amigable para el usuario
            configMINIMAL_STACK_SIZE*2, 		// Cantidad de stack de la tarea
            NULL,                          	// Parametros de tarea
            tskIDLE_PRIORITY,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
            NULL,                          		// Puntero a la tarea creada en el sistema
            0
        );
    // Gestion de errores
    if(res == pdFAIL)
    {
        printf( "Error al crear la tarea.\r\n" );
        while(true);					// si no pudo crear la tarea queda en un bucle infinito
    }

}

// Implementacion de funcion de la tarea
void tarealed( void* taskParmPtr )
{
    // ---------- Configuraciones ------------------------------
    for(int i = 0; i < N_PULSADOR; i++){
        
    gpio_pad_select_gpio(led[i]);
    gpio_set_direction(led[i], GPIO_MODE_OUTPUT);}

    TickType_t xPeriodicity =  PERIODO;
	TickType_t xLastWakeTime = xTaskGetTickCount();
    static TickType_t dif ;
    static uint8_t ind ;
    ledinfo *datosrecibidos;

    // ---------- Bucle infinito --------------------------
    while( true )
    {
        if(xQueueReceive( comandosLed , &datosrecibidos,  0 )) //recibo dato desde la cola sin tiempo de espera
        {
            dif = datosrecibidos->diferenciaTiempo;
            ind = datosrecibidos->indice1;
            //acá se recibió
            if( dif > xPeriodicity )
            {
                dif = xPeriodicity;
            }
        }
        else
        {
            //acá no se recibió
        }
         
        gpio_set_level( led[ind], 1 );
        vTaskDelay( dif );
        gpio_set_level( led[ind], 0 );

        vTaskDelayUntil( &xLastWakeTime , xPeriodicity );
    }
}