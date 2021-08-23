#include "lora.h"

bool init_lora(){
  bool status_init = false;
    Serial.println("[LoRa Sender] Tentando iniciar comunicacao com o radio LoRa...");
    SPI.begin(SCK,MISO,MOSI,SS); // LoRa SPI communication
    LoRa.setPins(SS,RST,DI0);
     
    if (!LoRa.begin(FREQ)) 
    {
        Serial.println("[LoRa Sender] Comunicacao com o radio LoRa falhou. Nova tentativa em 1 segundo...");        
        delay(1000);
        status_init = false;
    }
    else
    {
        LoRa.setSpreadingFactor(SF);
        LoRa.setSignalBandwidth(BAND);
        LoRa.setTxPower(TXPOWER);
        LoRa.enableCrc();
        Serial.println("[LoRa Sender] Comunicacao com o radio LoRa ok");
        status_init = true;
    }
 
    return status_init;
}

void send_msg_lora(String msg){
  /* Envia a informação */
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();

}
