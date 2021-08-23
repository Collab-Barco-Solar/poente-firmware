#include "sensors.h"

Adafruit_ADS1115 ads_battery_modules(BATTERY);

float BatteryVoltageRead(){
  ads_battery_modules.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit =   0.125mV

  int16_t result = ads_battery_modules.readADC_SingleEnded(0);
  float voltageRead = (result - (RESOLUTION_16BIT/2 - 1))*(LIMIT_GAIN_ONE/RESOLUTION_16BIT); 

  //Find voltage before voltage divider
  int R1 220000, R2 = 13300;  
  
  return voltageRead * (R1+R2)/R2;
}

float PVModulesVoltageRead(){
  ads_battery_modules.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit =   0.125mV

  int16_t result = ads_battery_modules.readADC_SingleEnded(0);
  float voltageRead = (result - (RESOLUTION_16BIT/2 - 1))*(LIMIT_GAIN_ONE/RESOLUTION_16BIT); 

  //Find voltage before voltage divider
  int R1 = 330000, R2 = 10000;  
  
  return voltageRead * (R1+R2)/R2;
}