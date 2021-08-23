#include "lora.h"

bool init_lora(){
  bool status_init = false;
    Serial.println("[LoRa Sender] Tentando iniciar comunicacao com o radio LoRa...");
    SPI.begin(SCK,MISO,MOSI,SS);
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
        LoRa.enableCrc();
        LoRa.receive();
        Serial.println("[LoRa Sender] Comunicacao com o radio LoRa ok");
        status_init = true;
    }
 
    return status_init;
}

void receber_dados_lora(){
  // try to parse packet
  int packetSize = LoRa.parsePacket();
//  Serial.println(packetSize);
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

//    // read packet
//    while (LoRa.available()) {
//      Serial.print((char)LoRa.read());
//    }

    String LoRaData = "";
    // read packet
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
    }

    Serial.print(LoRaData);

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
