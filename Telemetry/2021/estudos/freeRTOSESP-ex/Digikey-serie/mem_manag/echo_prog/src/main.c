#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/uart.h"

void testTask(void *pvParameter);

void app_main(void)
{
    uart_set_baudrate(UART_NUM_0, 9600);
    vTaskDelay(500/portTICK_PERIOD_MS);
    
    printf("---FreeRTOS Memory Demo---");    
    xTaskCreatePinnedToCore(&testTask, "Test Task", 2048, NULL, 1, NULL, 0);
    vTaskDelete(NULL);
}

void testTask(void *pvParameter)
{
    while(1)
    {
        int a = 1;
        int b[100];         
        for (int i = 0; i < 100; i++)
        {
            b[i] = a + 1;
        }
        printf("%d\n", b[0]);
        vTaskDelay(10/portTICK_PERIOD_MS);
        printf("High water mark (words): ");
        printf("%d \n", uxTaskGetStackHighWaterMark(NULL));
    }
}