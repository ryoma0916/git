#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <arduino.h>
#include <SD.h>
#include <JPEGDecoder.h>
#include <ili9328.h>
#include <SPI.h>
////////////////////////////////////////
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
///////////////////////////////////////
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <NTP.h>
//////////////////////////////////////

int button=2; 

#define CS 15 //sdCS 4
#define RESET 0

ili9328SPI tft(CS,RESET);

// Color definitions
#define BLACK       0x0000 

void setup() {

    Serial.begin (9600);
    Serial.println();
    tft.begin();
    tft.fillScreen(BLACK);
    tft.setCursor(0, 0);
    yield();
    /////////////////////////////////////////////////
    mp3_set_serial (Serial); 
    delay(1);           
    mp3_set_volume (20);  
    /////////////////////////////////////////////////
    Serial.println();
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    wifiManager.autoConnect("AutoConnect");
    
    ntp_begin(2390);
    setSyncInterval(36000);
    ////////////////////////////////////////////////
    Serial.println("");
    Serial.print("Initializing SD card...");

     if (!SD.begin(4)) { 
         Serial.println("initialization failed!");
          return;
      }
    Serial.println("initialization done.");

}

void loop() {
   int h = hour();
   int m = minute();
   char filename[] = (char)h);
   char time_m[] = (char)m);
   Serial.println(filename);
   Serial.println(time_m);
   SD.begin(4,400000);
   jpegDraw(filename);
   MinuteDraw(time_m);
   delay(30000);
   attachInterrupt(button,mp3,FALLING);
}

void mp3() {
  int h = hour();
  int m = minute();
  Serial.println(h);
  Serial.println(m);
     mp3_play (h);
     delay(100);
     mp3_play (m);
}

void MinuteDraw(char* time_m){
tft.setTextColor(0x0000); 
tft.setTextSize(5);  
tft.setCursor(135, 120); 
tft.println(time_m);
}

void jpegDraw(char* filename){
    Serial.println("start");
    char str[100];
    uint8 *pImg;
    int x,y,bx,by;
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
    
    for(;;)  yield();
}

