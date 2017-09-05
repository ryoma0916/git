#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <NTP.h>

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnect");
  
  ntp_begin(2390);
  setSyncInterval(36000);

  time_t n = now();
  time_t t;

  char s[20];
  const char* format = "%04d-%02d-%02d %02d:%02d:%02d";
  t = localtime(n, 9);
  sprintf(s, format, year(t), month(t), day(t), hour(t), minute(t), second(t));
  char hour(t);
}

void loop() {
  int h = hour();
  int m = minute();
  Serial.println(h+9);
  Serial.println(m);
  delay(2000);
}
