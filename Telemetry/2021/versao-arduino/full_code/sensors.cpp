#include "sensors.h"

Adafruit_ADS1115 ads_battery_modules(I2C_BATTERY);

const byte DEV_ADDR = 0x4D; // I2C address of the MCP3221
MCP3221 mcp3221(DEV_ADDR);

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


float Font12vVoltage(){
  int bitsRead = analogRead(PORT_12V_VM);
  float voltageRead = bitsRead * ESP_MAXIMUM_VOLTAGE_IN / 1023;  //Convert from bits to the float number representing the voltage read

  //Find voltage before voltage divider
  int R1 = 16000, R2 = 4700;  
  
  return voltageRead * (R1+R2)/R2;
}

float Font12vCurrent(){ //Verificar a necessidade de fazer várias leituras e pegar a maior ou a média
  // Read from ACS712
  int bitsRead = analogRead(PORT_12V_CM);
  float voltageRead = bitsRead * ESP_MAXIMUM_VOLTAGE_IN / 1023;  //Convert from bits to the float number representing the voltage read
  
  //Convert the voltage to the current in the ACS712
  return (voltageRead - ACS712_VCC/2)*1000/ACS712_OUTPUT_SENSITIVITY;
}

float MPPTCurrent(){ //Verificar a necessidade de fazer várias leituras e pegar a maior ou a média
  // Read from ACS758
  int bitsRead = analogRead(PORT_MPPT_CM);
  float voltageRead = bitsRead * ESP_MAXIMUM_VOLTAGE_IN / 1023;  //Convert from bits to the float number representing the voltage read
  
  //Convert the voltage to the current in the ACS758
  return (voltageRead - ACS758_VCC/2)*1000/ACS758_OUTPUT_SENSITIVITY;
}

float TemperatureRead(){
    // Read the voltage out from the temperature sensor TMP235AQDCKTQ1
    int bitsRead = analogRead(PORT_TEMP);
    float voltageRead = bitsRead * ESP_MAXIMUM_VOLTAGE_IN / 1023;  //Convert from bits to the float number representing the voltage read

    //Convert the voltage read to temperature https://pdf1.alldatasheetde.com/datasheet-pdf/view/1145216/TI1/TMP235AQDCKTQ1.html
    return (voltageRead * 1000/TEMP_SLOPE_OUT) - TEMP_OFFSET;
}

void setupMCP(){
  mcp3221.setVref(4096);               // sets voltage reference for the ADC in mV (change as needed)
  mcp3221.setVinput(VOLTAGE_INPUT_5V); // sets voltage input type to be measured (change as needed)
  mcp3221.setRes1(10000);              // sets exact value of the voltage divider's Resistor 1 for 12V readings (change as needed)
  mcp3221.setRes2(4700);               // sets exact value of the voltage divider's Resistor 2 for 12V readings (change as needed)
  mcp3221.setAlpha(178);               // sets the Alpha value used by the EMAVG smoothing method (change as needed)
}

unsigned int MCPVoltage(){
  return mcp3221.getVoltage();
}