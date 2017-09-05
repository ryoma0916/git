#include <arduino.h>
#include <SPI.h>
#include <SD.h>
#include <JPEGDecoder.h>


void setup() {
    Serial.begin(115200);
    while(!Serial); {
      ;
    }
    Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void loop() {
    Serial.println("start");
    char str[100];
    char filename[] = "test.jpeg";
    uint8 *pImg;
    int x,y,bx,by;
    SD.begin(4,400000);
    JpegDec.init();
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
    
    // Output CSV
    sprintf(str,"#SIZE,%d,%d",JpegDec.width,JpegDec.height);
    Serial.println(str);

    while(JpegDec.read()){
        pImg = JpegDec.pImage ;

        for(by=0; by<JpegDec.MCUHeight; by++){
        
            for(bx=0; bx<JpegDec.MCUWidth; bx++){
            
                x = JpegDec.MCUx * JpegDec.MCUWidth + bx;
                y = JpegDec.MCUy * JpegDec.MCUHeight + by;
                
                if(x<JpegDec.width && y<JpegDec.height){
                        sprintf(str,"#RGB,%d,%d,%u,%u,%u", x, y, pImg[0], pImg[1], pImg[2]);
                        Serial.println(str);
                        yield() ;
                }
                pImg += JpegDec.comps ;
            }
        }
    }
    for(;;);
    Serial.println("end");
    delay(1000);
}
