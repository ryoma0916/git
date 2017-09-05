#include <Wire.h>
#include <ST7032.h>
ST7032 lcd;
void setup() {
  Serial.begin(115200);
  lcd.beginESP(8,2,2,14);
  lcd.setContrast(32);
  lcd.print("hello, world!");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
}
