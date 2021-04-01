/* Hello World Example

   created from the tutorial "Hello_World_with_ESP32_Explained"
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

#define BLINK_GPIO 02

void hello_task(void *pvParameter)
{
    
    while(1)
    {
        printf("hello world!\n");
        vTaskDelay(100/ portTICK_RATE_MS);
    }

}

void blinky(void *pvParameter)
{
    gpio_pad_select_gpio(BLINK_GPIO);
    /* setting as output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1)
    {
        /* blink off (output) */
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000/ portTICK_RATE_MS);
        /* blink on (output) */
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000/ portTICK_RATE_MS);
    }
}

void app_main(void)
{
    xTaskCreate(&hello_task, "hello_task", 2048, NULL, 5, NULL);
    xTaskCreate(&blinky, "blinky", 512, NULL, 5, NULL);
}

