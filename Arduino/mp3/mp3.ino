
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(12,4); // RX,TX TXをRXに

void setup () {
pinMode(15,INPUT_PULLUP);
Serial.begin (115200);//デバッグ用
mySerial.begin (9600);//MP3モジュール操作用ソフトシリアル
mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module 
mp3_set_volume (20);
}

void loop () { 
  mp3_play(1);
  Serial.println("");
  Serial.println("1");
  delay(30000);
  mp3_play(2);
  Serial.println("");
  Serial.println("2");
  delay(30000);
}

