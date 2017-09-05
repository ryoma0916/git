#include <ESP8266WiFi.h>
#include <Servo.h>
#include <Wire.h>
#include <ST7032.h>
ST7032 lcd;

const char* ssid     = "HGuest";
const char* password = "Guest3478";
const char* host = "engawa2525.com";
int event_stat = 0;
int flag = 0;

void setup() {
  Serial.begin(115200);
  delay(10);
  lcd.beginESP(8,2,2,14);
  lcd.setContrast(32);
  lcd.print("hello");
  wifi();
}
void loop() {  
  pinMode(4,OUTPUT);
  pinMode(5,INPUT_PULLUP);
  attachInterrupt(5,stopLED,FALLING);
  readurl();
  if(event_stat == 1 && flag == 0) {
  digitalWrite(4,HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Happen");
  delay(600000);
  } else if (event_stat == 1 && flag == 1) {
  digitalWrite(4,HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Happen");
  delay(600000);
  } else {
  digitalWrite(4,LOW);
  lcd.setCursor(0, 0);
  lcd.print("No Event");
  flag = 0;
  delay(600000);
  }
  Serial.println();
  Serial.println("closing connection");
}

