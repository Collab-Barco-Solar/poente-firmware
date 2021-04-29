#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#define BUF_SIZE (1024)

#define BLINK_GPIO      02
#define DEAFULT_RATE    2000
int blink_rate;

void blinker(void* pvParameters)
{
    while(1)
    {
        // blink output low
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(blink_rate/portTICK_RATE_MS);
        // blink output high
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(blink_rate/portTICK_RATE_MS);
    }
}
static void set_blink_rate(void *arg)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_0, &uart_config);

    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);
    int pastblink = 0;
    while(1)
    {
       
        uart_read_bytes(UART_NUM_0, data, BUF_SIZE, 20 / portTICK_RATE_MS);
        blink_rate = atoi((const char*) data);
        if(pastblink != blink_rate)
        {
            printf("Blink rate: %d\n", blink_rate);
            pastblink = blink_rate;
            printf("%s\n", data);
        }       
        vTaskDelay(100/portTICK_RATE_MS);
    }
}

void app_main(void)
{
    //printf("Controlled blink Challenge\n");
    blink_rate = DEAFULT_RATE;

    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    xTaskCreate(&blinker, "blinker",512,NULL, 1, NULL);
    xTaskCreate(&set_blink_rate, "set_blink_rate",1024,NULL, 5, NULL);
}
