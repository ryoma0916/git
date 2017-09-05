 #include <ArduinoJson.h>
#include <FS.h>
#include <WiFiManager.h>
///////////////////////////
#include <FaBoLCDmini_AQM0802A.h>
//////////////////////////
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <SPI.h> 
#define ADDR 0x3e
extern "C" {
  #include "user_interface.h"
}
FaBoLCDmini_AQM0802A lcd;
char* host = "engawa2525.com";
int i=0;
String line = "";
bool event_stat= false;
String url = "/ondo/log?key=";
bool shouldSaveConfig = false;
String event_fri_no = "";
String event_no = "";
int LEDsta = 0 ;


void setup() {
  Serial.begin(115200);
  pinMode(15, INPUT_PULLUP); 
  pinMode(13,OUTPUT);
  pinMode(16,OUTPUT);
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("connected...yeey :)");
  lcd.begin();
 
}

void loop() {
  attachInterrupt(15,stopLED,RISING);
  wifi();  
  int error = line.indexOf("false"); 
  action(error);
  digitalWrite(13,LEDsta);
  delay(600000);
}
/////////////////////////////////////////

int build_event_fri_no(String line) {
  int enf = 0;
  enf =line.indexOf("efn=");
  if(enf != -1) {
    int num = numOf(line,enf+4);
    if(num != -1) {
      return num;
    }
  }
  return -1;
}
int numOf(String line,int idxenf) {
  char c = line.charAt(idxenf);
  String txt = "";
  int idx = idxenf;
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
  Serial.print("event_fridge_no=");
  Serial.println(txt);
  return txt.toInt();
}


 int build_event_no(String line) {
  int en = 0;
  en =line.indexOf("en=");
    int num = numOf2(line,en+3);
    if(num != -1) {
      return num;
    }
  return -1;
}
int numOf2(String line,int idxen) {
  char c = line.charAt(idxen);
  String txt = "";
  int idx = idxen;
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
  Serial.print("event_no=");
  Serial.println(txt);
  return txt.toInt();
}


 void write(uint8_t *cmd, size_t len) {
  size_t i;
  for (i=0; i<len; i++) {
    Wire.beginTransmission(ADDR);
    Wire.write(0x40);
    Wire.write(cmd[i]);
    Wire.endTransmission();
    delayMicroseconds(27);    // 26.3us
  }
}
  void command(uint8_t *cmd, size_t len) {
  size_t i;
  for (i=0; i<len; i++) {
    Wire.beginTransmission(ADDR);
    Wire.write(0x00);
    Wire.write(cmd[i]);
    Wire.endTransmission();
    delayMicroseconds(27);    // 26.3us
  }
}

void action(int error){
  if(error != -1) {
        LEDsta = 1;
        Serial.println("");
        Serial.println("event occer");
        event_no = build_event_no(line) ;
        event_fri_no= build_event_fri_no(line) ;
        lcd.setCursor(0, 0);
        lcd.print("Err_");
        lcd.setCursor(4, 0);
        lcd.print(event_no);
        lcd.setCursor(0, 1);
        lcd.print("Fri_");
        lcd.setCursor(4, 1);
        lcd.print(event_fri_no);
             
      }else{
        LEDsta = 0;
        Serial.println("event don't occer");
        lcd.setCursor(0, 0);
        lcd.print("No_Error");
        lcd.setCursor(0, 1);
        lcd.print("No_Error");
      }
}

void wifi(){
  WiFiClient client;
  const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  Serial.println(millis());
   client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
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
    line = client.readStringUntil('\r');
    Serial.print(line);
   }
}

void stopLED(){
  Serial.println("stop LED");
  digitalWrite(13,LOW);
}

