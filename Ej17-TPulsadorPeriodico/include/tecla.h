#ifndef tecla_h
#define tecla_h
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


#define led2    GPIO_NUM_26
#define cero 0

TickType_t tiempoA;           // se guarda la cantidad de ticks en alto
TickType_t tiempoB ;          // se guarda la cantidad de ticks en bajo
TickType_t tiempo_pulsado ;   // variable para almacenar los ticks contados
TickType_t diferencia;        // ta
typedef enum{

   BAJO,
   ESPERA1,
   ALTO,
   ESPERA2,

} estadoBoton_t;

estadoBoton_t estadoTECLA;

void config_pulsador(gpio_int_type_t tecla);

void actualizarpulsador(gpio_int_type_t PULSADOR1);

void contadorticksA();
void contadorticksB();
TickType_t tiempocontado(void);

#endif