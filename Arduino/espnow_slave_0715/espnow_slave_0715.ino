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

char* ssid = "hotland_wifi";
char* password = "wp_dnaltoh";
char* host = "engawa2525.com";
String line = "";
String url = "/ondo/log?key=";
uint8_t mac[][6] = {
  {0x5C,0xCF,0x7F,0xF4,0x3A,0x33},
  {0x5C,0xCF,0x7F,0x29,0xF7,0x36},
  {0x5C,0xCF,0x7F,0x32,0x92,0x7C},
  {0x5C,0xCF,0x7F,0x32,0x93,0xBC}
};
uint8_t arr[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
bool flag1 = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Initializing...");
  Serial.println("   I    ");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("test", "12345678", 1, 0);

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
  if (flag1 == 1) {
    WiFi.disconnect();
    wifi();
    sendurl();
    flag1 = 0;
    delay(1000);
    deepsleep(1000000);
    delay(1000);
  }
  delay(1000);
  
}


