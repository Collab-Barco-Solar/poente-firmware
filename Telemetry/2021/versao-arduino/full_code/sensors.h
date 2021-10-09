#ifndef __SENSORS_H__
#define __SENSORS_H__

#include <Arduino.h>
#include <Adafruit_ADS1015.h>
#include <MCP3221.h>

//I2C
#define I2C_BATTERY  0x48  // Endereco do medidor ADC da bateria A0 - Batery Bank voltage // A1 - PV modules voltage

//Temperature Sensor TMP235AQDCKTQ1 https://pdf1.alldatasheetde.com/datasheet-pdf/view/1145216/TI1/TMP235AQDCKTQ1.html
#define TEMP_SLOPE_OUT 10 //mV/°C
#define TEMP_OFFSET 50 //V

//ADS read
#define LIMIT_GAIN_ONE 4.096
#define RESOLUTION_16BIT 65536

//Constants
#define ESP_MAXIMUM_VOLTAGE_IN 3.3
#define ACS712_OUTPUT_SENSITIVITY 44 // 44 mV/A - for model ACS71240LLCBTR-030B3 https://www.digikey.be/product-detail/en/allegro-microsystems/ACS71240LLCBTR-030B3/620-2052-1-ND/10146687
#define ACS712_VCC 3.3
#define ACS758_OUTPUT_SENSITIVITY 40 // 40 mV/A - for model ACS758LCB-050B-PFF-T https://pdf1.alldatasheet.com/datasheet-pdf/view/533456/ALLEGRO/ACS758_13.html
#define ACS758_VCC 3.3

//Esp ports
#define PORT_12V_VM 33
#define PORT_12V_CM 13
#define PORT_MPPT_CM 32
#define PORT_TEMP 0



float BatteryVoltageRead();
float PVModulesVoltageRead();
float Font12vVoltage();
float Font12vCurrent();
float MPPTCurrent();
float TemperatureRead();
void setupMCP();
unsigned int MCPVoltage();

#endif
