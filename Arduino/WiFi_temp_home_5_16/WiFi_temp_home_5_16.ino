#include <ArduinoJson.h>
#include <Arduino.h>
#include <FS.h>
#include <WiFiManager.h>
///////////////////////////
#include <OneWire.h>
#include <DallasTemperature.h>
#define WIFI_DEFAULT_CHANNEL 1
#define ONE_WIRE_BUS 13
#define SENSER_BIT   9
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
///////////////////////////
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
extern "C" {
  #include "user_interface.h"
  #include <espnow.h>
  #include <user_interface.h>
}

char* host = "engawa2525.com";
int dst = 0;
int i = 0;
String line = "";
float h = 0;
float t = 0;
float f = 0;
float temp = 0;
float humi = 0;
String url = "/ondo/log?key=";
int wifitime = 0;
uint8_t mac[] = {0x5C,0xCF,0x7F,0xF4,0x3A,0x33};
uint8_t key[] = {0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44};
uint8_t data[6] = {0x0,0x0,0x0,0x0,0x0,0x0};

void setup() {
  Serial.begin(115200);
  espnow_slave();
  wifi();
  senddata();

}

void loop() {
  system_deep_sleep_set_option(0);
  system_deep_sleep(60000000);
  delay(10000);
} 


