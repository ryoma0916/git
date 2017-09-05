#include <BME280_MOD-1022.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SPI.h>
extern "C" {
  #include "user_interface.h"
}
const char* ssid     = "Buffalo-G-6A20";               // myRouter SSID
const char* password = "vyxwkknnmttw6";               // myRouter Password
const char* host = "engawa2525.com";     // thingspeak URL
const char* thingspeak_key = "test engawa";  // thingspeak Write KEY
 
void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5); delay(10);             // SDA=GPIO_13,SCL=GPIO_14
 
  BME280.readCompensationParams();           // read the NVM compensation parameters
  BME280.writeOversamplingTemperature(os1x); // 1x over sampling
  BME280.writeOversamplingHumidity(os1x);    // 1x over sampling
  BME280.writeOversamplingPressure(os1x);    // 1x over sampling
 
  Serial.println();Serial.println();Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) { delay(500);Serial.print(".");}
  Serial.println("");Serial.println("WiFi connected");Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  delay(5000);
  Serial.print("connecting to ");Serial.println(host);
  WiFiClient client;      // Use WiFiClient class to create TCP connections
  const int httpPort = 80;
  if (!client.connect(host,httpPort)){Serial.println("connection failed");return;}
 
  BME280.writeMode(smForced); // After taking the measurement the chip goes back to sleep
  while (BME280.isMeasuring()){Serial.println("Measuring...");delay(50);}
  Serial.println("Done!");
  BME280.readMeasurements();                     // read out the data
  String temp = String(BME280.getTemperature()); // Temp
  String humi = String(BME280.getHumidity());    // Humidity
  String pres = String(BME280.getPressure());    // Pressure
   
  String url = "/ondo/log?key=";
  url += thingspeak_key;                         // thingspeak Write KEY
  url += "&field1=";url += temp;                 // Temp
  url += "&field2=";url += humi;                 // Humidity
  url += "&field3=";url += pres;                 // Pressure  
  Serial.print("Requesting URL: ");Serial.println(url);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" +  
               "Connection: close\r\n\r\n");
               int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
        }
  }
 
  while(client.available()){
    String line = client.readStringUntil('\r');
    int vol = Serial.parseInt();
    int dst = vol*10000000;
    Serial.print(line);
    Serial.println();Serial.println("closing connection. going to sleep...");
  delay(100);
  system_deep_sleep_set_option(0);              // go to deepsleep for 10 minutes
  system_deep_sleep(dst);         // 1000000=1s
  } 
}
