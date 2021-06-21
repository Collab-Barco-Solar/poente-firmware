// blink crazy app

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

#define BLINK_GPIO 02

void blink1_taks(void *pvParameters)
{
    
    while(1)
    {
        // blink output low
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(500/portTICK_RATE_MS);
        // blink output high
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(500/portTICK_RATE_MS);
    }
}

void blink2_taks(void *pvParameters)
{
    
    while(1)
    {
        // blink output low
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(333/portTICK_RATE_MS);
        // blink output high
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(333/portTICK_RATE_MS);
    }
}

void app_main(void)
{
    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    xTaskCreate(&blink1_taks, "blink1_task", 512, NULL, 5, NULL);
    xTaskCreate(&blink2_taks, "blink2_task", 512, NULL, 5, NULL);
}