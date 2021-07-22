#include "gps.h"
#include "lora.h"

void setup()
{
  Serial.begin(115200);
  init_gps();
  /* Tenta, até obter sucesso, comunicacao com o chip LoRa */
  while(init_lora() == false);  
}

void loop()
{
  delay(1000);
  String result_gps = get_gps_info();
  Serial.println(result_gps);
  send_msg_lora(result_gps);
}
