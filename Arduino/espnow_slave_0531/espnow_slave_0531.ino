#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
extern "C" {
#include <espnow.h>
#include <user_interface.h>
}
#define WIFI_DEFAULT_CHANNEL 1

char* ssid = "Buffalo-G-6A20";
char* password = "vyxwkknnmttw6";
char* host = "engawa2525.com";
String line = "";
String url = "/ondo/log?key=";
uint8_t mac[][6] = {
  {0x5C,0xCF,0x7F,0xF4,0x3A,0x33},
  {0x5C,0xCF,0x7F,0xF4,0x3A,0x32}
 };
uint8_t arr[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
bool flag1 = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("test", "12345678", 1, 0);
  Serial.println("");
  uint8_t macaddr[6];
  wifi_get_macaddr(STATION_IF, macaddr);
  Serial.print("mac address (STATION_IF): ");
  printMacAddress(macaddr);

  wifi_get_macaddr(SOFTAP_IF, macaddr);
  Serial.print("mac address (SOFTAP_IF): ");
  printMacAddress(macaddr);

  if (esp_now_init() == 0) {
    Serial.println("init");
  } else {
    Serial.println("init failed");
    ESP.restart();
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb([](uint8_t *macaddr, uint8_t *data, uint8_t len) {
    Serial.println("recv_cb");
    flag1 = 1;
    Serial.print("mac address: ");
    printMacAddress(macaddr);

    Serial.print("data: ");
    for (int i = 0; i < len; i++) {
      Serial.print(data[i]);
      arr[i] = data[i];
      Serial.print(",");
    }
    Serial.println("");
  });
  
  int l = sizeof(mac) / sizeof(mac[0]);
  for (int i = 0; i < l; i++) {
    Serial.print("ch=");
    Serial.print(i);
    Serial.println(esp_now_add_peer(mac[i], (uint8_t)ESP_NOW_ROLE_CONTROLLER, (uint8_t)WIFI_DEFAULT_CHANNEL, NULL, 0));
  }
 }

void loop() {
if (flag1 == 1){
   WiFi.disconnect(); 
   wifi();
   sendurl();
   flag1 = 0;
   delay(1000);
   deepsleep(1000000);
   delay(1000);
    }
}


void printMacAddress(uint8_t* macaddr) {
  Serial.print("{");
  for (int i = 0; i < 6; i++) {
    Serial.print("0x");
    Serial.print(macaddr[i], HEX);
    if (i < 5) Serial.print(',');
  }
  Serial.println("}");
}

void wifi(){
  Serial.println();
  Serial.print("Connecting to ");
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  }

 void sendurl(){
       WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
  }
  url += arr[0];
  url += arr[1];
  url += arr[2];
  url += "&field1="; url += (arr[3]-50)/2;
  url += "&field2="; url += arr[4];
  url += "&field3="; url += arr[5];
  Serial.print("Requesting URL: "); Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  int timeout = millis() + 5000;
  Serial.println(millis());

  while (client.available() == 0) {

    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
 }
 void deepsleep(int howlong){
    ESP.deepSleep(howlong, WAKE_RF_DEFAULT);
}

