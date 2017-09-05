#include <ArduinoJson.h>
#include <FS.h>
#include <WiFiManager.h>
///////////////////////////
#include <DHT.h>
#define DHTTYPE DHT22
#define DHTPIN 4
DHT dht(DHTPIN, DHTTYPE);
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
char* host = "engawa2525.com";
char key[40];
int dst=0;
int i=0;
String line = "";
float h = 0;
float t = 0;
float f = 0;
float temp = 0;
float humi = 0;
String url = "/ondo/log?key=";
bool shouldSaveConfig = false;
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void setup() {
  pinMode(DHTPIN, INPUT); 
  Serial.begin(115200);
  pinMode(14, INPUT_PULLUP); 
  wifi();
  funkDHT22();
  WiFiClient client;
  const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  sendURL();
  readURL();
  wificonfig();
}

void loop() {
  int dst = buildDst(line);
  Serial.println("//////");
  Serial.println();
  Serial.print("closing connection. going to ");
  Serial.print(dst);
  Serial.println("sec sleep...");
  Serial.println(millis());
  system_deep_sleep_set_option(0);
  system_deep_sleep(dst*100000); 
  delay(1000);
}   //end of loop function
/////////////////////////////////////////
 int buildDst(String line) {
  Serial.println("buildDst");
  int t = 0;
  t =line.indexOf("true");
  int f = 0;
  f =line.indexOf("false");
  
  if(t != -1) {
    int num = numOf(line,t+4);
    if(num != -1) {
      return num;
    }
  }
  if(f != -1) {
    Serial.println("false");
    int num = numOf(line,f+5);
    if(num != -1) {
      return num;
    }
  }  
  return -1;
}

 int numOf(String line,int idx0) {
  char c = line.charAt(idx0);
  String txt = "";
  int idx = idx0;
  while(c >= '0' && c <= '9') {
    txt.concat(String(c));
    idx++;
    if(idx > line.length() -1) {
      break;
    }
    c = line.charAt(idx);
  }
  if(txt == "") {
    return -1;
  }
  return txt.toInt();
}

void wifi(){
  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");

          strcpy(key, json["custom_key"]);

        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  WiFiManager wifiManager;
   if (digitalRead(14)==LOW){
  wifiManager.resetSettings();
  }
  WiFiManagerParameter custom_key("key", "uniqekey", key, 40);

  wifiManager.setSaveConfigCallback(saveConfigCallback);

  wifiManager.addParameter(&custom_key);
  wifiManager.autoConnect();

 strcpy(key, custom_key.getValue());
 
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("connected...yeey :)");
}
void funkDHT22(){
   h = dht.readHumidity();
   t = dht.readTemperature();
   f = dht.readTemperature(true);
  while (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!"); 
   h = dht.readHumidity();
   t = dht.readTemperature();
   f = dht.readTemperature(true);
  }
  humi = h;
  temp = t;
  }
void wificonfig(){
   if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["custom_key"] = key;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
  }
}

void sendURL(){
  WiFiClient client;
  url += key;                         
  url += "&field1=";url += temp;    
  url += "&field2=";url += humi;   
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
void readURL(){
    WiFiClient client;
    while(client.available()){
    line = client.readStringUntil('\r');
    Serial.print(line);
  }
}
