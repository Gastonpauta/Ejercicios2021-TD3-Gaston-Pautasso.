
#ifndef tecla_h //chequea que otro archivo no haya llamado a pulsador.h

#define tecla_h

#include "driver/gpio.h"

typedef enum{

   BAJO,
   ESPERA1,
   ALTO,
   ESPERA2,

} estadoBoton_t;

estadoBoton_t estadoTECLA;

void config_pulsador(gpio_int_type_t tecla);

void actualizarpulsador(gpio_int_type_t PULSADOR1);

void actualizarestado(void);

#endif