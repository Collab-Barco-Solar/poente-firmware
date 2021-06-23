#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lora.h"

uint8_t buf[32];

void task_rx(void *p)
{
   int x;
   for(;;) {
      lora_receive();    // put into receive mode
      while(lora_received()) {
         x = lora_receive_packet(buf, sizeof(buf));
         buf[x] = 0;
         printf("Received: %s\n", buf);
         lora_receive();
      }
      vTaskDelay(pdMS_TO_TICKS(10));
   }
}

void task_wd(void *pvParameters)
{
   while(1)
   {
      printf("code running still...\n");
      vTaskDelay(pdMS_TO_TICKS(2000));
   }
}

void app_main()
{
   lora_init();
   lora_set_frequency(915e6);
   lora_enable_crc();
   xTaskCreate(&task_rx, "task_rx", 2048, NULL, 5, NULL);
   xTaskCreate(&task_wd, "task_wd", 1024, NULL, 1, NULL);
}