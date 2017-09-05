#include <arduino.h>
#include <SPI.h>
#include <FS.h>
#include <JPEGDecoder.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library

#define TFT_CS     15
#define TFT_RST    5
#define TFT_DC     4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  Serial.println("");
  delay(10);

  tft.initR(INITR_BLUETAB);
  tft.fillScreen(ST7735_BLACK);

  SPIFFS.begin();
  jpegDraw("/test1.jpg");
}

void jpegDraw(char* filename) {
  char str[100];
  uint8 *pImg;
  int x,y,bx,by;
  
  // Decoding start
  JpegDec.decode(filename,0);

  // Image Information
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
  
  sprintf(str,"#SIZE,%d,%d",JpegDec.width,JpegDec.height);
  Serial.println(str);

  // Raw Image Data
  while(JpegDec.read()){
    pImg = JpegDec.pImage ;

    for(by=0; by<JpegDec.MCUHeight; by++){
      for(bx=0; bx<JpegDec.MCUWidth; bx++){
        
        x = JpegDec.MCUx * JpegDec.MCUWidth + bx;
        y = JpegDec.MCUy * JpegDec.MCUHeight + by;
        
        if(x<JpegDec.width && y<JpegDec.height){
          if(JpegDec.comps == 1){ // Grayscale          
            tft.drawPixel(x, y, tft.Color565(pImg[0], pImg[0], pImg[0]));
          }else{ // RGB
            tft.drawPixel(x, y, tft.Color565(pImg[0], pImg[1], pImg[2]));
          }
        }
        
        pImg += JpegDec.comps ;
      }
    }
  }
}
    
void loop() {
}

