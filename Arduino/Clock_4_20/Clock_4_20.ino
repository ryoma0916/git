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

int button = 15;
int h = 0;
int m = 0;
int MC = 0;
int HC = 0;
  
char* HPic = "0014.jpg";
char* MPic = "min00.jpg";

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
  mp3_set_volume (30);
  pinMode(button,INPUT_PULLUP);
  
  ntp_begin(2390);
  
  SetPic();
  SetPicM();
  jpegDraw(HPic);
  jpegDraw_mini(MPic);
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
  SetTime();
      if(digitalRead(button)==HIGH){
            YukarinVoice();
          }
      if(minute() == 0){
            SetPic();    
            SetPicM();
            jpegDraw(HPic);
            jpegDraw_mini(MPic);
            delay(10);
            Serial.print(hour());Serial.print(": ");
            Serial.print(minute());Serial.print(": ");
            delay(50000);
          }else{
            Serial.print(hour());Serial.print(": ");
            Serial.print(minute());Serial.print(": ");
      }
      
      if(second() == 0 && minute() != 0){
            SetPicM();
            jpegDraw_mini(MPic);
            Serial.println(second());
           }else{
            Serial.println(second());
           }
           delay(100);
      }
//_________________________________________________________
void SetTime(){
  h = hour();
  m = minute();
  Serial.print(h+9);Serial.print(" : ");
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

void YukarinVoice(){
    Serial.println("yukarin voice");
      int Sound_hour = h+200;
      mp3_play(Sound_hour);
      Serial.print("hour :");
      Serial.println(Sound_hour);
      delay(1000);
      int Sound_minute = m+100;
      mp3_play(Sound_minute);
      Serial.print("minute :");
      Serial.println(Sound_minute);
      delay(1000);
      mp3_play(1);
      delay(1000);
}  

void MinuteDraw(int m){
  tft.writeFillRect(269,199,45,30,0xFFFF);
  delay(1);
  tft.setTextColor(0x3CDF); 
  tft.setTextSize(4);
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
if (hour() == 0){
    HPic = "0000.jpg";
}
else if (hour() == 1){
    HPic = "0001.jpg";
}
else if (hour() == 2){
    HPic = "0002.jpg";
}
else if (hour() == 3){
    HPic = "0003.jpg";
}
else if (hour() == 4){
    HPic = "0004.jpg";
}
else if (hour() == 5){
    HPic = "0005.jpg";
}
else if (hour() == 6){
    HPic = "0006.jpg";
}
else if (hour() == 7){
    HPic = "0007.jpg";
}
else if (hour() == 8){
    HPic = "0008.jpg";
}
else if (hour() == 9){
    HPic = "0009.jpg";
}
else if (hour() == 10){
    HPic = "0010.jpg";
}
else if (hour() == 11){
    HPic = "0011.jpg";
}
else if (hour() == 12){
    HPic = "0012.jpg";
}
else if (hour() == 13){
    HPic = "0013.jpg";
}
else if (hour() == 14){
    HPic = "0014.jpg";
}
else if (hour() == 15){
    HPic = "0015.jpg";
}
else if (hour() == 16){
    HPic = "0016.jpg";
}
else if (hour() == 17){
    HPic = "0017.jpg";
}
else if (hour() == 18){
    HPic = "0018.jpg";
}
else if (hour() == 19){
    HPic = "0019.jpg";
}
else if (hour() == 20){
    HPic = "0020.jpg";
}
else if (hour() == 21){
    HPic = "0021.jpg";
}
else if (hour() == 22){
    HPic = "0022.jpg";
}
else if (hour() == 23){
    HPic = "0023.jpg";
}
else if (hour() == 24){
    HPic = "0024.jpg";
}
}
void  SetPicM(){
if (minute() == 0){
    MPic = "min00.jpg";
}
else if (minute() == 1){
    MPic = "min01.jpg";
}
else if (minute() == 2){
    MPic = "min02.jpg";
}
else if (minute() == 3){
    MPic = "min03.jpg";
}
else if (minute() == 4){
    MPic = "min04.jpg";
}
else if (minute() == 5){
    MPic = "min05.jpg";
}
else if (minute() == 6){
    MPic = "min06.jpg";
}
else if (minute() == 7){
    MPic = "min07.jpg";
}
else if (minute() == 8){
    MPic = "min08.jpg";
}
else if (minute() == 9){
    MPic = "min09.jpg";
}
else if (minute() == 10){
    MPic = "min10.jpg";
}
else if (minute() == 11){
    MPic = "min11.jpg";
}
else if (minute() == 12){
    MPic = "min12.jpg";
}
else if (minute() == 13){
    MPic = "min13.jpg";
}
else if (minute() == 14){
    MPic = "min14.jpg";
}
else if (minute() == 15){
    MPic = "min15.jpg";
}
else if (minute() == 16){
    MPic = "min16.jpg";
}
else if (minute() == 17){
    MPic = "min017.jpg";
}
else if (minute() == 18){
    MPic = "min18.jpg";
}
else if (minute() == 19){
    MPic = "min19.jpg";
}
else if (minute() == 20){
    MPic = "min20.jpg";
}
else if (minute() == 21){
    MPic = "min21.jpg";
}
else if (minute() == 22){
    MPic = "min22.jpg";
}
else if (minute() == 23){
    MPic = "min23.jpg";
}
else if (minute() == 24){
    MPic = "min24.jpg";
}
else if (minute() == 25){
    MPic = "min25.jpg";
}
else if (minute() == 26){
    MPic = "min26.jpg";
}
else if (minute() == 27){
    MPic = "min27.jpg";
}
else if (minute() == 28){
    MPic = "min28.jpg";
}
else if (minute() == 29){
    MPic = "min29.jpg";
}
else if (minute() == 30){
    MPic = "min30.jpg";
}
else if (minute() == 31){
    MPic = "min31.jpg";
}
else if (minute() == 32){
    MPic = "min32.jpg";
}
else if (minute() == 33){
    MPic = "min33.jpg";
}
else if (minute() == 34){
    MPic = "min34.jpg";
}
else if (minute() == 35){
    MPic = "min35.jpg";
}
else if (minute() == 36){
    MPic = "min36.jpg";
}
else if (minute() == 37){
    MPic = "min37.jpg";
}
else if (minute() == 38){
    MPic = "min38.jpg";
}
else if (minute() == 39){
    MPic = "min39.jpg";
}
else if (minute() == 40){
    MPic = "min40.jpg";
}
else if (minute() == 41){
    MPic = "min41.jpg";
}
else if (minute() == 42){
    MPic = "min42.jpg";
}
else if (minute() == 43){
    MPic = "min43.jpg";
}
else if (minute() == 44){
    MPic = "min44.jpg";
}
else if (minute() == 45){
    MPic = "min45.jpg";
}
else if (minute() == 46){
    MPic = "min46.jpg";
}
else if (minute() == 47){
    MPic = "min47.jpg";
}
else if (minute() == 48){
    MPic = "min48.jpg";
}
else if (minute() == 49){
    MPic = "min49.jpg";
}
else if (minute() == 50){
    MPic = "min50.jpg";
}
else if (minute() == 51){
    MPic = "min51.jpg";
}
else if (minute() == 52){
    MPic = "min52.jpg";
}
else if (minute() == 53){
    MPic = "min53.jpg";
}
else if (minute() == 54){
    MPic = "min54.jpg";
}
else if (minute() == 55){
    MPic = "min55.jpg";
}
else if (minute() == 56){
    MPic = "min56.jpg";
}
else if (minute() == 57){
    MPic = "min57.jpg";
}
else if (minute() == 58){
    MPic = "min58.jpg";
}
else if (minute() == 59){
    MPic = "min59.jpg";
}
}
void jpegDraw(char* HPic){
    Serial.println("start");
    char str[100];
    char* filename = HPic;
    uint8 *pImg;
    int x,y,bx,by;
    SD.begin(2,40000000);
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
                    if(x >= 0 && x < 320 && y >= 0 && y < 240) {
                        tft.drawPixel(x, y, tft.color565(pImg[0], pImg[0], pImg[0]));
                      }
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

void jpegDraw_mini(char* HPic){
    Serial.println("start");
    char str[100];
    char* filename = HPic;
    uint8 *pImg;
    int x,y,bx,by;
    SD.begin(2,40000000);
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
                    if(x >= 0 && x < 320 && y >= 0 && y < 240) {
                        tft.drawPixel(x, y, tft.color565(pImg[0], pImg[0], pImg[0]));
                      }
                    }else{ // RGB
                      if(x >= 0 && x < 320 && y >= 0 && y < 240) {
                        tft.drawPixel(x+230, y+180, tft.color565(pImg[0], pImg[1], pImg[2]));
                      }
                    }
                }
                pImg += JpegDec.comps ;
            }
        }
    }
}

