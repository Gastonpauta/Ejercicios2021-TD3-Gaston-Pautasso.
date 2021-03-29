void app_main() {
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BLINK_GPIO CONFIG_BLINK_GPIO

void app_main() 
{
    gpio_pad_select_gpio(BLINK_GPIO);

    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
      
    }
    
}
