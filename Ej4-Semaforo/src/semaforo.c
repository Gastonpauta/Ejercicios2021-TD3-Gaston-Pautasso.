#include "../include/semaforo.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define tiempo_rojo 5000/portTICK_PERIOD_MS
#define tiempo_verde 3000/portTICK_PERIOD_MS
#define tiempo_amarillo 500/portTICK_PERIOD_MS

void secuencia_semaforo(int led_rojo,int led_amarillo,int led_verde){

	gpio_set_level(led_rojo,1);
		vTaskDelay(tiempo_rojo);
    gpio_set_level(led_rojo,0);
    gpio_set_level(led_amarillo,1);
        vTaskDelay(tiempo_amarillo);
    gpio_set_level(led_amarillo,0);
    gpio_set_level(led_verde,1);
        vTaskDelay(tiempo_verde);
    gpio_set_level(led_verde,0);
    gpio_set_level(led_amarillo,1);
        vTaskDelay(tiempo_amarillo);
    gpio_set_level(led_amarillo,0);
    gpio_set_level(led_rojo,1);
			    }

void secuencia_intermitente(int led_rojo,int led_amarillo,int led_verde){

    gpio_set_level(led_verde,0);
    gpio_set_level(led_rojo,0);
    gpio_set_level(led_amarillo,1);
        vTaskDelay(tiempo_amarillo);
    gpio_set_level(led_amarillo,0);
}