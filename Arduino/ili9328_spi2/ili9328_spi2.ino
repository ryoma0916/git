#include <SPI.h>
#define ROW 320
#define COL 240
#define pin_CS  15
#define pin_RST 0

#define COLOR_BLACK 0x0000
#define COLOR_BLUE 0x001f
#define COLOR_RED 0xf800
#define COLOR_PURPLE 0xf81f
#define COLOR_GREEN 0x07e0
#define COLOR_CYAN 0x07ff
#define COLOR_YELLOW 0xffe0
#define COLOR_WHITE 0xffff
int color_table[8] = {
  COLOR_BLACK ,
  COLOR_BLUE ,
  COLOR_RED ,
  COLOR_PURPLE ,
  COLOR_GREEN ,
  COLOR_CYAN ,
  COLOR_YELLOW ,
  COLOR_WHITE
};
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif
//接続
//
//  1　VCC_IN --> 5V
//  2　GND    --> GND
//  3　D_CS   --> (arduino)D10
//  4　D_RST  --> (arduino)D5
//  5　D_RS   --> 接続なし
//  6　D_SDI  --> (arduino)D11
//  7　D_SCK  --> (arduino)D13
//  8　D_LED  --> GND BackLight
//  9　D_SDO  --> 接続なし
//
 
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
  //SendDataSPI(0x72);
  SPI.transfer(0x72);
  //SendDataSPI(i>>8);
  SPI.transfer(i>>8);
  //SendDataSPI(i);
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
void drawPixel(int x, int y, unsigned int color)
{
  unsigned int i,j;
//  digitalWrite(pin_CS, 0);
  WriteComm(0x0050);WriteData(x);
  WriteComm(0x0051);WriteData(x); 
  WriteComm(0x0052);WriteData(y);   
  WriteComm(0x0053);WriteData(y);  
//writeRegister16(0x0020, x);
  WriteComm(0x0020);WriteData(x);
//writeRegister16(0x0021, y);
  WriteComm(0x0021);WriteData(y);
//writeRegister16(0x0022, color);
  WriteComm(0x0022);WriteData(color);
//  digitalWrite(pin_CS, 1);
}
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    _swap_int16_t(x0, y0);
    _swap_int16_t(x1, y1);
  }
  if (x0 > x1) {
    _swap_int16_t(x0, x1);
    _swap_int16_t(y0, y1);
  }
  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);
  int16_t err = dx / 2;
  int16_t ystep;
  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }
  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}
void BoxFill(int x, int y, int width, int height, unsigned int color1)
{
  unsigned int i,j;
//  digitalWrite(pin_CS, 0);
 
  BlockWrite(x,x+width-1,y,y+height-1);
 
  for(i=0;i<width;i++){
    for(j=0;j<height;j++){   
      WriteData(color1);
    }
  }
//  digitalWrite(pin_CS, 1);
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
//  int localCOL = 80;
//  int localROW = 80;
//  unsigned int i,j;
//  digitalWrite(pin_CS, 0);
//  BlockWrite(40,localCOL-1,40,localROW-1);
//  for(i=0;i<localROW;i++){
//    for(j=0;j<localCOL;j++){   
//      WriteData(color1);
//    }
//  }
//  digitalWrite(pin_CS, 1);
}
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
 // Update in subclasses if desired!
//  for (int16_t i=x; i<x+w; i++) {
//    drawFastVLine(i, y, h, color);
//  }
  BoxFill(x, y, w, h, color);
}
void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;
  drawPixel(x0  , y0+r, color);
  drawPixel(x0  , y0-r, color);
  drawPixel(x0+r, y0  , color);
  drawPixel(x0-r, y0  , color);
  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}
void drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;
  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    }
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }
}
void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
  //drawLine(x, y, x, y+h-1, color);
  BoxFill(x, y, 1, h, color);
 
}
void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
  //drawLine(x, y, x+w-1, y, color);
  BoxFill(x, y, w, 1, color);
}
void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  drawFastHLine(x, y, w, color);
  drawFastHLine(x, y+h-1, w, color);
  drawFastVLine(x, y, h, color);
  drawFastVLine(x+w-1, y, h, color);
}
void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color)
{
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;
  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}
void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
  drawFastVLine(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}
void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
  // smarter version
  drawFastHLine(x+r  , y    , w-2*r, color); // Top
  drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
  drawFastVLine(x    , y+r  , h-2*r, color); // Left
  drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
  // draw four corners
  drawCircleHelper(x+r    , y+r    , r, 1, color);
  drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
  drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}
void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
  // smarter version
  fillRect(x+r, y, w-2*r, h, color);
  // draw four corners
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}
void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}
void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
  int16_t a, b, y, last;
  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
  }
  if (y1 > y2) {
    _swap_int16_t(y2, y1); _swap_int16_t(x2, x1);
  }
  if (y0 > y1) {
    _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
  }
  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    drawFastHLine(a, y0, b-a+1, color);
    return;
  }
  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
  int32_t
    sa   = 0,
    sb   = 0;
  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it
  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) _swap_int16_t(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }
  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) _swap_int16_t(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }
}

int MakeColorGray(int Kosa)
{
  int red = Kosa << 11;
  int green = Kosa << 6;
  int blue = Kosa;
  return red+green+blue;
}


void setup() {
  Serial.begin(115200);
  Serial.println("setup start");
 
  pinMode(pin_CS, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE2);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
 
  LCD_Init();
 
  for(int y=0;y<320;y+=16){
    for(int x=0;x<240;x+=8){
      unsigned int color = random(0, 65535);
      BoxFill(x, y, 8, 16, color);
      yield();
    }
  }
  Serial.println("setup end");
}
void loop() {
   BoxFill(0, 0, 240, 320, 64);
    for(int i=0;i<5000;i++){
      unsigned int color = random(0, 260000);
      unsigned int x = random(0, 240/10);
      unsigned int y = random(0, 320/10);
      BoxFill(x*10, y*10, 10, 10, color);
      yield();
    }
    // pixel random
  BoxFill(0, 0, 240, 320, 4032);
  for(int i=0;i<50000;i++){
    unsigned int color = random(0, 260000);
    drawPixel(random(0, 240), random(0, 320), color );
  yield();
  }
// circle random
  BoxFill(0, 0, 240, 320,258048 );
  for(int i=0;i<500;i++){
    drawCircle(random(50, 190), random(50, 280), random(0, 50), color_table[random(1, 7)]);
  yield();
  }
    Serial.println("end");
    delay(1000);
}
