#include <Arduino.h>
#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
  #include <user_interface.h>
}
#define WIFI_DEFAULT_CHANNEL 1
///////////////////////////
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 13
#define SENSER_BIT   9 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
///////////////////////////

uint8_t mac[] = {0x5E,0xCF,0x7F,0x29,0xD5,0xDF};
int place_num = 01;
int shop_num = 00;
int fridge_num = 01;
float temp = 0;
int random_num1 = 0;
int random_num2 = 0;
int ran = random(10);
int dst = 0;

void setup() {
  Serial.begin(115200);
  DS18B20();
  random_num1 = random(250);
  random_num2 = random(250);
  temp = (2*temp) + 50;
  uint8_t arr[] = {place_num,shop_num,fridge_num,temp,random_num1,random_num2};
  espnow_con(arr);
  dst = ran + 60;
  delay(3000);
  Serial.println(dst);
  Serial.println("sleep");
  deepsleep(dst*1000000);
}

void loop() {
  delay(1000);
}



