#include <ESP8266WiFi.h>
 
void setup() {
  Serial.begin(115200);     //  adjust your Arduino IDE Serial monitor
 
  byte mac[6];
  WiFi.macAddress(mac);
  char buf[20];
  Serial.println("");
  Serial.print("MAC address:   ");
  sprintf(buf,"%02X:%02X:%02X:%02X:%02X:%02X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
  Serial.print(buf);
  sprintf(buf,"   %02x%02x%02x%02x%02x%02x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
  Serial.println(buf);
}
 
void loop() {
  delay(1000);    //  dummy
}
