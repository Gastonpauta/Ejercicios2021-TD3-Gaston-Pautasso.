#ifndef led_h
#define led_h

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

TickType_t delay ;

#define led           GPIO_NUM_32  //led de tarea principal
#define led_debug     GPIO_NUM_33   //led para debug

void crear_tarea(void);     // funcion que crea la tarea

#endif