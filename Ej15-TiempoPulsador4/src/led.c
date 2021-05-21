#include "../include/led.h"
#include "../include/tecla.h"

#define retardo  15
#define retardo_     pdMS_TO_TICKS(retardo)
void tarealed( void * pvParameters );
TaskHandle_t xHandle1 = NULL; 

void crear_tarea(void){

xTaskCreatePinnedToCore( 

                  tarealed,                  //Función que implementa la tarea. La misma no debe retornar.
                 "Tarea led",                //Nombre que reprenta la tarea, para facilitar la depuración.
                 configMINIMAL_STACK_SIZE,   //Tamaño del stack en bytes
                 NULL,                       //Puntero que se utilizará como parámetro para la tarea que se está creando. Como no lo usamos ponemos NULL
                 tskIDLE_PRIORITY+1,         //Prioridad de la tarea
                 &xHandle1,                  //Puntero a la tarea
                 0                           //Procesador donde se ejecuta la tarea
                );

gpio_set_level(led_debug, 0); // se coloca este led para saber si la tarea se vuelve a crear
configASSERT( xHandle1 );                    
}

void tarealed( void * pvParameters )
{
    gpio_pad_select_gpio(led); 
    gpio_set_direction(led, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(led_debug);
    gpio_set_direction(led_debug, GPIO_MODE_OUTPUT);


while (true)
    {

    delay = tiempocontado();   //le asignamos a la variable delay la cantidad de ticks mientras el pulsador estuvo presionado 

        if (delay>cero){

           gpio_set_level(led, 1);
           vTaskDelay(delay);
           gpio_set_level(led,0);
           borrarticks();           // funcion para borrar la diferencia de ticks
             }
/*borramos la tarea una vez que realiza su funcion*/
        if( xHandle1 != NULL ){
            gpio_set_level(led_debug, 1); // se coloca este led para saber si la tarea es eliminada
            vTaskDelete( xHandle1 );    //Elimina la tarea
            xHandle1 = NULL;}
    else
        {
            vTaskDelay( retardo_ );
        }

    }
}