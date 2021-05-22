#include "../include/tecla.h"


#define T_REBOTE_MS   15
#define T_REBOTE pdMS_TO_TICKS(T_REBOTE_MS)

static int pulsador_uno; 

void tarea_pulsador( void * pvParameters );

TaskHandle_t xHandle2 = NULL;            //Puntero a la tarea

void config_pulsador(gpio_int_type_t tecla)
{
    pulsador_uno= tecla;
    estadoTECLA = BAJO;  
    gpio_pad_select_gpio(led2);                //replica lo que hace el pulsador
    gpio_set_direction(led2, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(pulsador_uno);
    gpio_set_direction(pulsador_uno, GPIO_MODE_INPUT); //Configura el pin como entrada digital
    gpio_set_pull_mode(pulsador_uno, GPIO_PULLDOWN_ONLY); //Habilita resistencia de PULLDOWN interna

    xTaskCreatePinnedToCore( 
                  tarea_pulsador,                  //Función que implementa la tarea. La misma no debe retornar.
                 "Tarea pulsador",                //Nombre que reprenta la tarea, para facilitar la depuración.
                 configMINIMAL_STACK_SIZE*2,   //Tamaño del stack en bytes
                 NULL,                      
                 tskIDLE_PRIORITY+1,       //mayor prioridad que el led
                 &xHandle2,                  //Puntero a la tarea
                 1                 //Procesador donde se ejecuta la tarea
                );
configASSERT( xHandle2 );                    //entra si no se pudieron crear las tareas, para debug

        if( xHandle2 == NULL )
        {
          vTaskDelete( xHandle2 );
        }
}

void actualizarpulsador(gpio_int_type_t PULSADOR1){
    
switch (estadoTECLA){

case BAJO:

    if(gpio_get_level(PULSADOR1) == 1)
    {
     estadoTECLA = ESPERA1 ;
    }
    break ;

case ESPERA1:

    if (gpio_get_level(PULSADOR1) == 1)
    {
       contadorticksA();
	   estadoTECLA = ALTO;
    }
    break;
//		
case ALTO:

    if (gpio_get_level(PULSADOR1) == 0)
    {

	estadoTECLA = ESPERA2;
                                       }
              
        break;
//
case ESPERA2:

    if (gpio_get_level(PULSADOR1) == 0)
           {
           contadorticksB();
	       estadoTECLA = BAJO;
           }
    
        break;
//
default:
        estadoTECLA = BAJO;
	    break;
}}
void contadorticksA(){
    TickType_t conteoTicksActuales = xTaskGetTickCount();   //Medimos el tiempo en ticks desde que inició el scheduler
    gpio_set_level(led2 , 1);        
    tiempoA = conteoTicksActuales;           
}


void contadorticksB()
    {
    TickType_t conteoTicksActuales = xTaskGetTickCount();   //Medimos el tiempo en ticks desde que inició el scheduler
    gpio_set_level(led2, 0 );     
    tiempoB  = conteoTicksActuales;
    diferencia = tiempoB-tiempoA;   
    }

TickType_t tiempocontado()
   {
    tiempo_pulsado= diferencia ;
    return tiempo_pulsado;
   }

void tarea_pulsador( void* taskParmPtr )
{
    while(1)
    {
        actualizarpulsador(pulsador_uno);
        vTaskDelay(T_REBOTE);
    }
}
