#define MONITOR_SPEED 115200
#define GPS_TX 15
#define GPS_RX 12
#define GPS_SERIAL_SPEED 9600
#define GPS_SATTELITES_TO_TRUST 7
#define UPDATE_PERIOD_MS 2000
#define SOFT_SERIAL_INVERT false
#define SOFT_SERIAL_BUF_SIZE 256

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

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

void gpsPosition(SoftwareSerial &serial, TinyGPSPlus &gps, gpsCoordinate &gc)
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

void updatePosition()
{
  gpsPosition(ss, gps, g);
  Serial.print("Latitude : ");
  Serial.println(g.latitude, 8);
  Serial.print("Longitude : ");
  Serial.println(g.longitude, 8);
  Serial.print("Altitude : ");
  Serial.println(g.altitude);
  Serial.print("Data Age : ");
  Serial.println(g.age);
  Serial.print("Sattellites : ");
  Serial.println(g.sattelites);
  Serial.print("Speed : ");
  Serial.println(g.speed);
  // Must-have cast. Somehow if you don`t print it you lose precision in your numbers :-P
  Serial.println((String) "");
}

void updatePositionTask()
{
  unsigned long currentTime = millis();
  if ((unsigned long)(currentTime - previousGpsUpdate) >= UPDATE_PERIOD_MS)
  {
    updatePosition();
    // RESET timer
    previousGpsUpdate = millis();
  }
}

void setup()
{
  Serial.begin(MONITOR_SPEED);
  ss.begin(GPS_SERIAL_SPEED, GPS_RX, GPS_TX, SWSERIAL_8N1, SOFT_SERIAL_INVERT, SOFT_SERIAL_BUF_SIZE);
}

void loop()
{
  updatePositionTask();
}