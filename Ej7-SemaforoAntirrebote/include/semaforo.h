#define semaforo_h

#include <stdio.h>
#include "driver/gpio.h"


typedef enum{
    ROJO,
    AMARILLO,
    VERDE,
    RESTART,
    INTERMITENTE,
    INTERMITENTEOFF
} estadoMEF_t;
// Variable de estado (global)
estadoMEF_t estadoActual;
//
void Iniciar_semaforo(void) ;
void Actualizar_semaforo(void);