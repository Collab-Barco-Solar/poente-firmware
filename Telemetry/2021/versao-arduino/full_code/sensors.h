#ifndef __SENSORS_H__
#define __SENSORS_H__

#include <Arduino.h>
#include <Adafruit_ADS1015.h>


//ADS read
#define BATTERY  0x48  // Endereco do medidor ADC da bateria A0 - Batery Bank voltage // A1 - PV modules voltage
#define LIMIT_GAIN_ONE 4.096
#define RESOLUTION_16BIT 65536

//Constants
#define ESP_MAXIMUM_VOLTAGE_IN 3.3
#define ACS712_OUTPUT_SENSITIVITY 44 // 44 mV/A - for model ACS71240LLCBTR-030B3 https://www.digikey.be/product-detail/en/allegro-microsystems/ACS71240LLCBTR-030B3/620-2052-1-ND/10146687
#define ACS712_VCC 3.3

//Esp ports
#define PORT_12V_VM 32
#define PORT_12V_CM 33



float BatteryVoltageRead();
float PVModulesVoltageRead();
float Font12vVoltage();
float Font12vCurrent();

#endif
