#include "lora.h"

int counter = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

 /* Tenta, até obter sucesso, comunicacao com o chip LoRa */
  while(init_lora() == false);  
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  send_msg_lora("0.00000000,0.00000000,12.35,"+String(counter));

  counter++;

  delay(1000);
}
