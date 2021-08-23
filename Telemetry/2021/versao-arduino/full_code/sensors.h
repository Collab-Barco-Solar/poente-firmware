#ifndef __SENSORS_H__
#define __SENSORS_H__

#include <Arduino.h>
#include <Adafruit_ADS1015.h>


//ADS read
#define BATTERY  0x48  // Endereco do medidor ADC da bateria A0 - Batery Bank voltage // A1 - PV modules voltage
#define LIMIT_GAIN_ONE 4.096
#define RESOLUTION_16BIT 65536





float BatteryVoltageRead();
float PVModulesVoltageRead();

#endif
