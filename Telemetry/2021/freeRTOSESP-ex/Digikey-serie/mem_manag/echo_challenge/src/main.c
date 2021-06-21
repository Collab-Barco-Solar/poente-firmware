#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/uart.h"

#define BUF_SIZE 1024

void listen_uart_task(void *pvParameter);
void echo_uart_task(void *pvParameter);
void configure_uart_task(void *pvParameter);

char *msg_ptr;
bool received = false;

void app_main() 
{
    vTaskDelay(100/portTICK_PERIOD_MS);
    

    xTaskCreatePinnedToCore(&configure_uart_task,"Uart Configure", 1024, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(&listen_uart_task,"Uart listener", 2048, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(&echo_uart_task,"Uart echo", 1024, NULL, 1, NULL, 0);
    vTaskDelete(NULL);
}

void configure_uart_task(void *pvParameter)
{
    uart_config_t uart_config = {
        .baud_rate = 300,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_0, &uart_config);
    printf("UART ECHO - MEMORY MANAGEMENT\n");
    vTaskDelete(NULL);
}

void listen_uart_task(void *pvParameter)
{
    unsigned char c[10];
    c[0] = '\0';
    memset(c, 0, 9);
    uint16_t buf_pos = 0;
    char buffer[BUF_SIZE];
    while(1)
    {   
        uart_read_bytes(UART_NUM_0, c, 1,20 / portTICK_PERIOD_MS);
        if((buf_pos < BUF_SIZE) && (c[0] != '\0'))
        {
            buffer[buf_pos] = c[0];
            printf("%c\n", buffer[buf_pos]);
            c[0] = '\0';
            buf_pos++;
        }
        if(buffer[buf_pos-1] == '\n')
        {
            printf("tem um barra n\n");
            buffer[buf_pos-1] = '\0';
            if(received == false)
            {                               
                msg_ptr = (char*) malloc(8*(buf_pos+1));
                configASSERT(msg_ptr);
                memcpy(msg_ptr, (const char*) buffer, buf_pos);
                received = true;
            }            
            buf_pos = 0;
        }
      
        vTaskDelay(100/portTICK_RATE_MS);
    } 

}

void echo_uart_task(void *pvParameter)
{
    while (1)
    {
        if(received)
        {
            printf("%s\n", msg_ptr);
            received = false;
            vPortFree(msg_ptr);
            msg_ptr = NULL;
        }
        vTaskDelay(100/portTICK_RATE_MS);
    }
    
}