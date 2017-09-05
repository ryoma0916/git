#include <Arduino.h>
#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
  #include <user_interface.h>
}

#define WIFI_DEFAULT_CHANNEL 1

uint8_t mac[] = {0x5C,0xCF,0x7F,0x29,0xF8,0x2F};
uint8_t key[] = {0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44};

void setup() {
  pinMode(13, OUTPUT);

  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("foobar", "12345678", 1, 0);

  uint8_t macaddr[6];
  wifi_get_macaddr(STATION_IF, macaddr);
  wifi_get_macaddr(SOFTAP_IF, macaddr);
  if (esp_now_init() == 0) {
    Serial.println("init");
  } else {
    Serial.println("init failed");
    ESP.restart();
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  
  esp_now_register_recv_cb([](uint8_t *macaddr, uint8_t *data, uint8_t len) {
  Serial.println("Hello");
  });
  
  int res = esp_now_add_peer(mac, (uint8_t)ESP_NOW_ROLE_CONTROLLER,(uint8_t)WIFI_DEFAULT_CHANNEL, key, 16);

//  esp_now_unregister_recv_cb();
//  esp_now_deinit();
}

void loop() {
}
