
#include <SPI.h>
#define ROW 320
#define COL 240
#define pin_CS 2
#define pin_RST 5

void WriteComm(unsigned int i)
{
  digitalWrite(pin_CS, 0);
//  SendDataSPI(0x70);
   SPI.transfer(0x70);
//  SendDataSPI(i>>8);
   SPI.transfer(i>>8);
//  SendDataSPI(i);
   SPI.transfer(i & 0xff);
  digitalWrite(pin_CS, 1);
}
void WriteData(unsigned int i)
{
  digitalWrite(pin_CS, 0);
  SPI.transfer(0x72);
  SPI.transfer(i>>8);
  SPI.transfer(i & 0xff);
  digitalWrite(pin_CS, 1);
}
void LCD_CtrlWrite_ILI9325C(unsigned int com,unsigned int dat)
{
  WriteComm(com);
  WriteData(dat);
}
void LCD_Init(void)
{
  digitalWrite(pin_RST, 1);
  delay(100);
  digitalWrite(pin_RST ,0);
  delay(500);
  digitalWrite(pin_RST, 1);
  delay(500);
 
  LCD_CtrlWrite_ILI9325C(0x00E5, 0x78F0);     // set SRAM internal timing
  LCD_CtrlWrite_ILI9325C(0x0001, 0x0000);     // s et SS and SM bit
  LCD_CtrlWrite_ILI9325C(0x0002, 0x0400);     // s et 1 line inversion
  LCD_CtrlWrite_ILI9325C(0x0003, 0x1090);     // s et GRAM write direction and BGR=1. 
  LCD_CtrlWrite_ILI9325C(0x0004, 0x0000);     // Resize register
  LCD_CtrlWrite_ILI9325C(0x0008, 0x0202);     // s et the back porch and front porch
  LCD_CtrlWrite_ILI9325C(0x0009, 0x0000);     // s et non-display area refresh cycle ISC[3:0]
  LCD_CtrlWrite_ILI9325C(0x000A, 0x0000);     // FMARK function
  LCD_CtrlWrite_ILI9325C(0x000C, 0x0000);     // RGB interface setting
  LCD_CtrlWrite_ILI9325C(0x000D, 0x0000);     // Frame marker Position
  LCD_CtrlWrite_ILI9325C(0x000F, 0x0000);     // RGB interface polarity
  //*************Power On sequence **************** //
  LCD_CtrlWrite_ILI9325C(0x0010, 0x0000);       // SAP, BT[3:0], AP, DSTB, SLP, STB
  LCD_CtrlWrite_ILI9325C(0x0011, 0x0007);       // DC1[2:0], DC0[2:0], VC[2:0]
  LCD_CtrlWrite_ILI9325C(0x0012, 0x0000);       // VREG1OUT voltage
  LCD_CtrlWrite_ILI9325C(0x0013, 0x0000);       // VDV[4:0] for VCOM amplitude
  LCD_CtrlWrite_ILI9325C(0x0007, 0x0001);
  delay(200);                             // Dis-charge capacitor power voltage
  LCD_CtrlWrite_ILI9325C(0x0010, 0x1690);       // SAP, BT[3:0], AP, DSTB, SLP, STB
  LCD_CtrlWrite_ILI9325C(0x0011, 0x0227);       // Set DC1[2:0], DC0[2:0], VC[2:0]
  delay(50);                       // delay 50ms  
  LCD_CtrlWrite_ILI9325C(0x0012, 0x008C);       // External reference voltage= Vci;           
  delay(50);                       // delay 50ms
  LCD_CtrlWrite_ILI9325C(0x0013, 0x1500);       //VDV[4:0] for VCOM amplitude  0X1000
  LCD_CtrlWrite_ILI9325C(0x0029, 0x0004);       // VCM[5:0] for VCOMH      0X0009
  LCD_CtrlWrite_ILI9325C(0x002B, 0x000D);       //Set Frame Rate
  delay(50);                               // delay 50ms
  LCD_CtrlWrite_ILI9325C(0x0020, 0x0000);       // GRAM horizontal Address
  LCD_CtrlWrite_ILI9325C(0x0021, 0x0000);       // GRAM Vertical Address 
  // ----------- Adjust the Gamma   Curve ----------//
  LCD_CtrlWrite_ILI9325C(0x0030, 0x0000);
  LCD_CtrlWrite_ILI9325C(0x0031, 0x0607);
  LCD_CtrlWrite_ILI9325C(0x0032, 0x0305);
  LCD_CtrlWrite_ILI9325C(0x0035, 0x0000);
  LCD_CtrlWrite_ILI9325C(0x0036, 0x1604);
  LCD_CtrlWrite_ILI9325C(0x0037, 0x0204);
  LCD_CtrlWrite_ILI9325C(0x0038, 0x0001);
  LCD_CtrlWrite_ILI9325C(0x0039, 0x0707);
  LCD_CtrlWrite_ILI9325C(0x003C, 0x0000);
  LCD_CtrlWrite_ILI9325C(0x003D, 0x000F);
  //------------------ Set GRAM area ---------------//
  LCD_CtrlWrite_ILI9325C(0x0050, 0x0000);      // Horizontal GRAM Start Address
  LCD_CtrlWrite_ILI9325C(0x0051, 0x00EF);      // Horizontal GRAM End Address
  LCD_CtrlWrite_ILI9325C(0x0052, 0x0000);      // Vertical GRAM Start Address
  LCD_CtrlWrite_ILI9325C(0x0053, 0x013F);      // Vertical GRAM Start Address
  LCD_CtrlWrite_ILI9325C(0x0060, 0xA700);      // Gate Scan Line
  LCD_CtrlWrite_ILI9325C(0x0061, 0x0001);      // NDL,VLE, REV
  LCD_CtrlWrite_ILI9325C(0x006A, 0x0000);      //  set scrolling line
  //-------------- Partial Display Control ---------//
  LCD_CtrlWrite_ILI9325C(0x0080, 0x0000);
  LCD_CtrlWrite_ILI9325C(0x0081, 0x0000);
  LCD_CtrlWrite_ILI9325C(0x0082, 0x0000);
  LCD_CtrlWrite_ILI9325C(0x0083, 0x0000);
  LCD_CtrlWrite_ILI9325C(0x0084, 0x0000);
  LCD_CtrlWrite_ILI9325C(0x0085, 0x0000);
  //-------------- Panel Control -------------------//
  LCD_CtrlWrite_ILI9325C(0x0090, 0x0010);
  LCD_CtrlWrite_ILI9325C(0x0092, 0x0600);
  LCD_CtrlWrite_ILI9325C(0x0007, 0x0133);      // 262K color and display ON
}
void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend)
{
  WriteComm(0x0050);WriteData(Xstart);
  WriteComm(0x0051);WriteData(Xend); 
  WriteComm(0x0052);WriteData(Ystart);   
  WriteComm(0x0053);WriteData(Yend);  
  WriteComm(0x0020);
  WriteData(Xstart);
  WriteComm(0x0021);
  WriteData(Ystart);
  WriteComm(0x0022);
}
void DispColor(unsigned int color1)
{
  unsigned int i,j;
  digitalWrite(pin_CS, 0);
  BlockWrite(0,COL-1,0,ROW-1);
  for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++){   
      WriteData(color1);
    }
  }
  digitalWrite(pin_CS, 1);
}
void setup() {
  Serial.begin(115200);
  Serial.println("setup start");
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE2);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  pinMode(pin_CS, OUTPUT);
  pinMode(pin_RST, OUTPUT);
  LCD_Init();
 
  Serial.println("setup end");
}
void loop() {
  Serial.println("RED start");
  DispColor(0xf800); 
  Serial.println("RED end");
  delay(1000);
  Serial.println("GREEN start");
  DispColor(0x0ff0);   
  Serial.println("GREEN end");
  delay(1000);
  Serial.println("BLUE start");
  DispColor(0x001f);
  Serial.println("BLUE end");
  delay(1000);
  Serial.println("WHITE start");
  DispColor(0xffff);  
  Serial.println("WHITE end");
  delay(1000);
}

