#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_system.h"
#include "esp_spi_flash.h"


// #if CONFIG_FREERTOS_UNICORE
//     static const BaseType_t app_cpu = 0;
// #else
//     static const BaseType_t app_cpu = 1;
// #endif

// strings to print
const char msg[] = "testando uma frase grande. Nao sei se ja e grande o bastante. Ja deu? acho que sim. Entao ta tudo certo.";
const char msg2[] = "joao agricio lopes";
// // Task Handles
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

//**************************************************

// prints serial terminal with lower priority
void messagetask(void *pvParameter)
{
    int msglen = strlen(msg);

    while(1)
    {
        printf("\n");
        for(int i = 0; i < (msglen+1); i++)
        {
            printf("%c", msg[i]);
            for(int i = 0; i < 100000; i++)
            {
                __asm__ __volatile__("nop");
            }
        }
        printf("\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
}

void joaoagricio(void *pvParameter)
{
    int msglen = strlen(msg2);

    while(1)
    {
        printf("\n");
        for(int i = 0; i < (msglen+1); i++)
        {
            printf("%c", msg2[i]);  
            
        }   
        
        printf("\n");     
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
    
}

void asteriscprint(void *pvParameter)
{
    while(1)
    {
        printf("*");
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}
void handler_task(void *pvParameter)
{
    
    for(int i=0; i<20; i++)
    {
        vTaskSuspend(task_1);
        vTaskDelay(2000/ portTICK_PERIOD_MS);
        vTaskResume(task_1);
        vTaskDelay(2000/ portTICK_PERIOD_MS);
    }
    vTaskSuspend(task_1);
    if(task_1 != NULL)
    {
        vTaskDelete(task_1);    
        task_1 = NULL;
        vTaskDelete(NULL);
    }
}

void app_main(void)
{   
    uart_set_baudrate(UART_NUM_0, 300);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    printf("Main task running on core ");
    printf("%d", xPortGetCoreID());
    printf(" With priority");
    printf(" %d\n", uxTaskPriorityGet(NULL));
    xTaskCreatePinnedToCore(&messagetask, "messagetask", 2048, NULL, 1, &task_1, 1);
    xTaskCreatePinnedToCore(&asteriscprint, "asteriscprint", 1024, NULL, 2, &task_2, 1);
    xTaskCreatePinnedToCore(&joaoagricio, "joaoagricio", 1024, NULL, 2, NULL, 1);
    xTaskCreatePinnedToCore(&handler_task, "handler_task", 2048, NULL, 1, NULL, 1);
}
