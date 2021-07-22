#include "lora.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);

  /* Tenta, até obter sucesso, comunicacao com o chip LoRa */
    while(init_lora() == false);    
}

void loop() {
  receber_dados_lora();
}
