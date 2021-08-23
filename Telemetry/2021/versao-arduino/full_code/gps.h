#ifndef __GPS_H__
#define __GPS_H__

#define MONITOR_SPEED 115200
#define GPS_TX 15
#define GPS_RX 12
#define GPS_SERIAL_SPEED 9600
#define GPS_SATTELITES_TO_TRUST 7
#define UPDATE_PERIOD_MS 1000
#define SOFT_SERIAL_INVERT false
#define SOFT_SERIAL_BUF_SIZE 256

#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

void init_gps();
String get_gps_info();

#endif
