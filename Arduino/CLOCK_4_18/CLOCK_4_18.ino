#include <ESP8266WiFi.h>
#include <NTP.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <arduino.h>
#include <SD.h>
#include <JPEGDecoder.h>
#include <ili9328.h>
#include <SPI.h>

#include <SD.h>

SoftwareSerial mySerial(10,4);

int buttom = 15;
int h = 0;
int m = 0;
char* HPic = "0";

#define CS 5//sdcs 2
#define RESET 0
ili9328SPI tft(CS,RESET);
#define BLACK       0x0000 

void setup() {
  Serial.begin(115200);
  Wifi();
  TFTSetup();
  Serial.println();
  mySerial.begin (9600);
  mp3_set_serial (mySerial);
  mp3_set_volume (20);
  pinMode(buttom,INPUT_PULLUP);

  ntp_begin(2390);
//__________________________________________________
    Serial.println("");
    Serial.print("Initializing SD card...");

     if (!SD.begin(2)) { 
         Serial.println("initialization failed!");
          return;
      }
    Serial.println("initialization done.");
}

void loop() {
  attachInterrupt(buttom,StartMusic,RISING); 
  SetTime();
  SetPic();
  jpegDraw(HPic);
  TimeDraw(m);
  delay(60000);
}
//_________________________________________________________
void SetTime(){
  h = hour();
  m = minute();
  Serial.println(h+9);
  Serial.println(m);
}

void Wifi(){
  WiFi.begin("Buffalo-G-6A20", "vyxwkknnmttw6");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void StartMusic(){
  Serial.println("start music");
  int h = minute();
  int m = minute();
  mp3_play(h);
  mp3_play(m);
}  

void TimeDraw(int m){
  tft.writeFillRect(269,199,35,22,0xF000);
  delay(1);
  tft.setTextColor(0x3CDF); 
  tft.setTextSize(3);
  tft.setCursor(270,200); 
  tft.println(m);
}

void TFTSetup(){
  tft.begin();
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  yield();
}

void  SetPic(){

    HPic = "0000.jpg";

}

void  SetPic1(){
if (hour() == 0){
    HPic = "0000.jpeg";
}
else if (hour() == 1){
    HPic = "0001.jpeg";
}
else if (hour() == 2){
    HPic = "0002.jpeg";
}
else if (hour() == 3){
    HPic = "0003.jpeg";
}
else if (hour() == 4){
    HPic = "0004.jpeg";
}
else if (hour() == 5){
    HPic = "0005.jpeg";
}
else if (hour() == 6){
    HPic = "0006.jpeg";
}
else if (hour() == 7){
    HPic = "0007.jpeg";
}
else if (hour() == 8){
    HPic = "0008.jpeg";
}
else if (hour() == 9){
    HPic = "0009.jpeg";
}
else if (hour() == 10){
    HPic = "0010.jpeg";
}
else if (hour() == 11){
    HPic = "0011.jpeg";
}
else if (hour() == 12){
    HPic = "0012.jpeg";
}
}

void jpegDraw(char* HPic){
    Serial.println("start");
    char str[100];
    char* filename = HPic;
    uint8 *pImg;
    int x,y,bx,by;
    SD.begin(2,400000);
    JpegDec.init();
    JpegDec.decode(filename,0);
    Serial.println(filename);
    
    Serial.print("Width     :");
    Serial.println(JpegDec.width);
    Serial.print("Height    :");
    Serial.println(JpegDec.height);
    Serial.print("Components:");
    Serial.println(JpegDec.comps);
    Serial.print("MCU / row :");
    Serial.println(JpegDec.MCUSPerRow);
    Serial.print("MCU / col :");
    Serial.println(JpegDec.MCUSPerCol);
    Serial.print("Scan type :");
    Serial.println(JpegDec.scanType);
    Serial.print("MCU width :");
    Serial.println(JpegDec.MCUWidth);
    Serial.print("MCU height:");
    Serial.println(JpegDec.MCUHeight);
    Serial.println("");
    
    // Output CSV
    sprintf(str,"#SIZE,%d,%d",JpegDec.width,JpegDec.height);
    Serial.println(str);

    while(JpegDec.read()){
        pImg = JpegDec.pImage ;

        for(by=0; by<JpegDec.MCUHeight; by++){
            yield();
        
            for(bx=0; bx<JpegDec.MCUWidth; bx++){
                yield();
            
                x = JpegDec.MCUx * JpegDec.MCUWidth + bx;
                y = JpegDec.MCUy * JpegDec.MCUHeight + by;
                
                if(x<JpegDec.width && y<JpegDec.height){

                    if(JpegDec.comps == 1){ 
                    
                        sprintf(str,"#RGB,%d,%d,%u", x, y, pImg[0]);
                        Serial.println(str);

                    }else{ // RGB
                      if(x >= 0 && x < 320 && y >= 0 && y < 240) {
                        tft.drawPixel(x, y, tft.color565(pImg[0], pImg[1], pImg[2]));
                      }
                    }
                }
                pImg += JpegDec.comps ;
            }
        }
    }
}

