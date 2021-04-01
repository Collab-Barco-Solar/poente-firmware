// blink crazy app

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

#define BLINK_GPIO 02
#define BTN1_GPIO 13
#define BTN2_GPIO 25

void blink1_task(void *pvParameters)
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

void read_buttons(void *pvParameters)
{
    int btn1, btn2;

    while(1)
    {
        btn1 = gpio_get_level(BTN1_GPIO);
        btn2 = gpio_get_level(BTN2_GPIO);
    

        printf("Botao 1: %d, Botao 2: %d\n", btn1, btn2);
        vTaskDelay(400/portTICK_RATE_MS);
    }
    
}

void app_main(void)
{
    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_pad_select_gpio(BTN1_GPIO);
    gpio_pad_select_gpio(BTN2_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(BTN1_GPIO, GPIO_MODE_INPUT);
    gpio_set_direction(BTN2_GPIO, GPIO_MODE_INPUT);
    gpio_pullup_en(BTN1_GPIO);
    gpio_pullup_en(BTN2_GPIO);
    
    xTaskCreate(&blink1_task, "blink1_task", 512, NULL, 5, NULL);
    xTaskCreate(&blink2_taks, "blink2_task", 512, NULL, 5, NULL);
    xTaskCreate(&read_buttons, "read_buttons", 2048, NULL, 5, NULL);
}