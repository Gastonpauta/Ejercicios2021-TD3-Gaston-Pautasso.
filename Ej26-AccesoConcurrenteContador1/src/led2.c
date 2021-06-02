#include "led2.h"


void tareatres( void* taskParmPtr );
extern int contador ;
portMUX_TYPE mux3 = portMUX_INITIALIZER_UNLOCKED; //Inicializa el spinlock desbloqueado
void creartareatres(){

        BaseType_t res = xTaskCreatePinnedToCore( 

                  tareatres,                  //Función que implementa la tarea. La misma no debe retornar.
                 "Tarea tres",                //Nombre que reprenta la tarea, para facilitar la depuración.
                 configMINIMAL_STACK_SIZE*2,   //Tamaño del stack en bytes
                 NULL,                       //Puntero que se utilizará como parámetro para la tarea que se está creando. Como no lo usamos ponemos NULL
                 tskIDLE_PRIORITY+1,         //Prioridad de la tarea
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
void tareatres( void * pvParameters )
{

    static TickType_t xPeriodicity = PERIODO2 ; 	
    static TickType_t delay2 ;		   
    TickType_t xLastWakeTime = xTaskGetTickCount(); // Guarda en la variable la cantidad de ticks
    gpio_pad_select_gpio(led2); 
    gpio_set_direction(led2, GPIO_MODE_OUTPUT);

while (true){

    portENTER_CRITICAL(&mux3);
    delay2 = pdMS_TO_TICKS(2*contador);
    if (contador>100)
    {
        contador= contador - 100;
    }
    portEXIT_CRITICAL(&mux3);
    gpio_set_level(led2, 1);
    vTaskDelay(delay2);
    gpio_set_level(led2,0);

    vTaskDelayUntil( &xLastWakeTime , xPeriodicity ); //espera a que el tiempo del periodo se cumpla
}}