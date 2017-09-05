///////////////////////////
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 14
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
}
char* ssid = "Engawa Aoyama Time Capsule";  
char* password = "zakura1234567"; 
char* host = "engawa2525.com";
char* key = "engawa_test_5_31";
int dst=0;
int i=0;
String line = "";
float temp = 0;
String url = "/ondo/log?key=";

void setup() {
  Serial.begin(115200);
  DS18B20();
  wifi();
  WiFiClient client;
  const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  url += key;        
  url += "&field1=";url += temp;    
  url += "&field2=";url += millis();   
  url += "&field3=";url += 0.00;   
  Serial.print("Requesting URL: ");Serial.println(url);
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
void loop() {
  Serial.println("//////");
  Serial.println();
  Serial.print("closing connection. going to ");
  Serial.println("1 min sleep...");
  Serial.println(millis());
  system_deep_sleep_set_option(0);
  system_deep_sleep(900000000);
  delay(1000);
}   //end of loop function
/////////////////////////////////////////

void wifi(){
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); 
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);Serial.print(".");
    i = i+1;
    if (i==50){
        system_deep_sleep_set_option(0);
        system_deep_sleep(10000000);
        delay(1000);
    }
    }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  }

void DS18B20(){
  sensors.begin();
  sensors.setResolution(SENSER_BIT);
  sensors.requestTemperatures();
  Serial.println("DONE");
  Serial.print("Temperature for the device 1 (index 0) is: ");
  temp = sensors.getTempCByIndex(0);
  while (temp == -127.00)
  {
  Serial.println("REMESURE");
  system_deep_sleep_set_option(0);
  system_deep_sleep(3000000);
  delay(1000);
  }
  Serial.println(temp);
  }



