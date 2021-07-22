#include "gps.h"

void setup()
{
  Serial.begin(115200);
  init_gps();
}

void loop()
{
  String result_gps = get_gps_info();
  Serial.println(result_gps);
  delay(1000);
  
}
