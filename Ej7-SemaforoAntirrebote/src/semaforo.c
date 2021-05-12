#include "../include/semaforo.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/led.h"
#include "../include/tecla.h"

static int contador = 0 ; //contador de ciclos       

// Inicializo maquina de estados 
void Iniciar_semaforo(void){
	 estadoActual = ROJO;
}
// Función Actualizar MEF
void Actualizar_semaforo(void)
{
//
//
    contador++;	//incremento el contador por cada ciclo

switch (estadoActual) {
        
	case ROJO:
        {
            secuencia('R');
			if(contador == 100 ){
                contador = 0 ;
				 estadoActual = AMARILLO;
			}
		}
		break;
		case AMARILLO:
        {
            secuencia('A');
			if(contador == 100 ){
                contador = 0 ;
				 estadoActual = VERDE;
        }}
		break;
		case VERDE:{

        secuencia('V');

			if(contador == 100 ){
                contador = 0 ;
				 estadoActual = RESTART;
			}
		}
		break;

        case RESTART:{
        secuencia('A');

			if(contador == 100 ){
                contador = 0 ;
				 estadoActual = ROJO;}}
		break;

        case INTERMITENTE:{
        secuencia('I');

			if(contador == 100){
                contador = 0 ;
				 estadoActual = INTERMITENTEOFF;
				 }
		}
		break;

		case INTERMITENTEOFF:{
        secuencia('O');

			if(contador == 100){
                contador = 0 ;
				 estadoActual = INTERMITENTE;
				 }
		}	
		break;	 
		default:{
			//Si cae en un estado no valido, reinicio
			Iniciar_semaforo();
		}
		break;}}