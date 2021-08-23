#ifndef __LORA_H__
#define __LORA_H__

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

/* Definicoes para comunicação com radio LoRa */
#define SCK       5     // GPIO5  -- LoRa SX1278's SCK
#define MISO      19    // GPIO19 -- LoRa SX1278's MISnO
#define MOSI      27    // GPIO27 -- LoRa SX1278's MOSI
#define SS        18    // GPIO18 -- LoRa SX1278's CS
#define RST       14    // GPIO14 -- LoRa SX1278's RESET
#define DI0       26    // GPIO26 -- LoRa SX1278's IRQ(Interrupt Request)
 
#define FREQ  915E6   // Operating LoRa frequency
#define SF      7     // Operating LoRa Spread Factor
#define BAND  125E3   // Operating LoRa Bandwidth
#define TXPOWER 20    // Operating LoRa Transmition Power
#define BAUD 2000000  // BAUD serial rate

bool init_lora();
void send_msg_lora(String msg);

#endif
