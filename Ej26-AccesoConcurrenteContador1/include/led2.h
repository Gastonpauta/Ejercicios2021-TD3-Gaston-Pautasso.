#ifndef LED2_H_
#define LED2_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void creartareatres();
#define led2         GPIO_NUM_33  
#define PERIODO2     pdMS_TO_TICKS(2000) //Periodo fijo cada 1 segundo



#endif