#ifndef __LORA_H__
#define __LORA_H__

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

/* Definicoes para comunicação com radio LoRa */
#define SCK_LORA           5
#define MISO_LORA          19
#define MOSI_LORA          27
#define RESET_PIN_LORA     23
#define SS_PIN_LORA        18
 
#define HIGH_GAIN_LORA     20  /* dBm */
#define BAND               915E6  /* 915MHz de frequencia */

bool init_lora();
void receber_dados_lora();

#endif
