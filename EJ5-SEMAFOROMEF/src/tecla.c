#include "../include/tecla.h"
#include "../include/semaforo.h"



void config_pulsador(gpio_int_type_t tecla)
{
    estadoTECLA = BAJO;  
    gpio_pad_select_gpio(tecla);
    gpio_set_direction(tecla, GPIO_MODE_INPUT); //Configura el pin como entrada digital
    gpio_set_pull_mode(tecla, GPIO_PULLDOWN_ONLY); //Habilita resistencia de PULLDOWN interna
}

void actualizarBoton(gpio_int_type_t PULSADOR1){

switch (gpio_get_level(PULSADOR1)) //leemos el valor del pulsador 1
{
case 1: 
    estadoTECLA = ALTO;
    break;
case 0:
    estadoTECLA = BAJO;
    break;
default:

    break;
}}

