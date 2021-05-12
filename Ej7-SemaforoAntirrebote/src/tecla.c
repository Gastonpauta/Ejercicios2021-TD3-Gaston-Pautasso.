#include "../include/tecla.h"
#include "../include/semaforo.h"

static int retardo = 3 ;
static int k = 0 ;
void config_pulsador(gpio_int_type_t tecla)
{
    estadoTECLA = BAJO;  
    gpio_pad_select_gpio(tecla);
    gpio_set_direction(tecla, GPIO_MODE_INPUT); //Configura el pin como entrada digital
    gpio_set_pull_mode(tecla, GPIO_PULLDOWN_ONLY); //Habilita resistencia de PULLDOWN interna
}

void actualizarpulsador(gpio_int_type_t PULSADOR1){

    

switch (estadoTECLA)
{
case BAJO:{

    if(gpio_get_level(PULSADOR1) == 1){
        
     estadoTECLA = ESPERA1 ;
    }
    }
    break ;

case ESPERA1:{

    if ((gpio_get_level(PULSADOR1) == 1) && retardo < 1){

	estadoTECLA = ALTO;
    }
    retardo -- ;
    }
        break;
//		
    case ALTO:{

    if (gpio_get_level(PULSADOR1) == 0){

	estadoTECLA = ESPERA2;}
    if (k==0)
        {
           estadoActual = ROJO ;
           k=1;
        }
    else{
            estadoActual = INTERMITENTE ;
           k=0;
        }
        }
        break;
case ESPERA2:{

    if (((gpio_get_level(PULSADOR1) == 0) && retardo < 1)){

	    estadoTECLA = BAJO;
        }
    retardo -- ;
        }
        break;

default:
        estadoTECLA = BAJO;
	    break;
}}
