#include "gps.h"

// Loop-Multitask time control
unsigned long previousGpsUpdate = 0;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss;

typedef struct
{
  bool trust;
  double latitude;
  double longitude;
  double altitude;
  double speed;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t day;
  uint8_t month;
  int16_t year;
  uint32_t sattelites;
  uint32_t age;
} gpsCoordinate;

gpsCoordinate g;

void init_gps(){
  ss.begin(GPS_SERIAL_SPEED, GPS_RX, GPS_TX, SWSERIAL_8N1, SOFT_SERIAL_INVERT, SOFT_SERIAL_BUF_SIZE);
}


static void gpsPosition(SoftwareSerial &serial, TinyGPSPlus &gps, gpsCoordinate &gc)
{
  gc.trust = false;
  while (serial.available() > 0)
  {
    gps.encode(serial.read());
    if (gps.location.isUpdated() && (gc.trust == false))
    {
      if (gps.satellites.value() >= GPS_SATTELITES_TO_TRUST)
      {
        gc.latitude = gps.location.lat();
        gc.longitude = gps.location.lng();
        gc.altitude = gps.altitude.meters();
        gc.day = gps.date.day();
        gc.month = gps.date.month();
        gc.year = gps.date.year();
        gc.hour = gps.time.hour();
        gc.minute = gps.time.minute();
        gc.second = gps.time.second();
        gc.sattelites = gps.satellites.value();
        gc.age = gps.date.age();
        gc.speed = gps.speed.kmph();
        gc.trust = true;
      }
    }
  }
}


String get_gps_info(){
  String result = "";
  result = String(g.latitude, 8) + "," + String(g.longitude, 8) + "," + String(g.speed);
    
  unsigned long currentTime = millis();
  if ((unsigned long)(currentTime - previousGpsUpdate) >= UPDATE_PERIOD_MS)
  {
    gpsPosition(ss, gps, g);
    
    // RESET timer
    previousGpsUpdate = millis();
  }
  return result;
}
