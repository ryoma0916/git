#include "ili9328.h"

#if defined(ESP8266)
SPISettings setting(40000000, MSBFIRST, SPI_MODE2);
#elif defined(ESP32)
SPISettings setting(40000000, MSBFIRST, SPI_MODE2);
#else
SPISettings setting(8000000, MSBFIRST, SPI_MODE3);
#endif

ili9328SPI::ili9328SPI(uint8_t cs, uint8_t reset) : Adafruit_GFX(TFT_WIDTH, TFT_HEIGHT)
{
  CSpin = cs;
  RSTpin = reset;
}

void ili9328SPI::begin(void)
{
  CSPinSet = digitalPinToBitMask(CSpin);
  CSPort = portOutputRegister(digitalPinToPort(CSpin));
  pinMode(CSpin, OUTPUT);
  pinMode(RSTpin, OUTPUT);
  SPI.begin();
  init();
}

void ili9328SPI::init(void)
{
  digitalWrite(RSTpin, HIGH);
  delay(100);
  digitalWrite(RSTpin, LOW);
  delay(500);
  digitalWrite(RSTpin, HIGH);
  delay(500);
  writereg16(0x00E5, 0x78F0);
  writereg16(0x0001, 0x0000);
  writereg16(0x0002, 0x0400);
  writereg16(0x0003, 0x1090);
  writereg16(0x0004, 0x0000);
  writereg16(0x0008, 0x0202);
  writereg16(0x0009, 0x0000);
  writereg16(0x000A, 0x0000);
  writereg16(0x000C, 0x0000);
  writereg16(0x000D, 0x0000);
  writereg16(0x000F, 0x0000);
  writereg16(0x0010, 0x0000);
  writereg16(0x0011, 0x0007);
  writereg16(0x0012, 0x0000);
  writereg16(0x0013, 0x0000);
  writereg16(0x0007, 0x0001);
  delay(200);
  writereg16(0x0010, 0x1690);
  writereg16(0x0011, 0x0227);
  delay(50);
  writereg16(0x0012, 0x008C);
  delay(50);
  writereg16(0x0013, 0x1500);
  writereg16(0x0029, 0x0004);
  writereg16(0x002B, 0x000D);
  delay(50);
  writereg16(0x0020, 0x0000);
  writereg16(0x0021, 0x0000);
  writereg16(0x0030, 0x0000);
  writereg16(0x0031, 0x0607);
  writereg16(0x0032, 0x0305);
  writereg16(0x0035, 0x0000);
  writereg16(0x0036, 0x1604);
  writereg16(0x0037, 0x0204);
  writereg16(0x0038, 0x0001);
  writereg16(0x0039, 0x0707);
  writereg16(0x003C, 0x0000);
  writereg16(0x003D, 0x000F);
  writereg16(0x0050, 0x0000);
  writereg16(0x0051, 0x00EF);
  writereg16(0x0052, 0x0000);
  writereg16(0x0053, 0x013F);
  writereg16(0x0060, 0xA700);
  writereg16(0x0061, 0x0001);
  writereg16(0x006A, 0x0000);
  writereg16(0x0080, 0x0000);
  writereg16(0x0081, 0x0000);
  writereg16(0x0082, 0x0000);
  writereg16(0x0083, 0x0000);
  writereg16(0x0084, 0x0000);
  writereg16(0x0085, 0x0000);
  writereg16(0x0090, 0x0010);
  writereg16(0x0092, 0x0600);
  writereg16(0x0007, 0x0133);
}

void ili9328SPI::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  SPI.beginTransaction(setting);
  setblock(x, x + w, y, y + h);
  for (uint16_t i = 0; i < w + 1; i++)
  {
    for (uint16_t j = 0; j < h + 1; j++)
    {
      writedat16(color);
    }
  }
  SPI.endTransaction();
}

void ili9328SPI::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{  
  SPI.beginTransaction(setting);
  setblock(x, x, y, y + h);
  for (uint16_t j = 0; j < h + 1; j++)
  {
    writedat16(color);
  }
  SPI.endTransaction();
}

void ili9328SPI::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
  SPI.beginTransaction(setting);
  setblock(x, x + w, y, y);
  for (uint16_t j = 0; j < w + 1; j++)
  {
    writedat16(color);
  }
  SPI.endTransaction();
}

void ili9328SPI::drawPixel(int16_t x, int16_t y, uint16_t color) {
  SPI.beginTransaction(setting);
  //NOT WORKING CODE
  /*int16_t rx, ry;
  switch (rotation) {
    case 1:
      rx = y;
      ry = TFT_HEIGHT - x;
      break;
    case 2:
      rx = TFT_WIDTH - x;
      ry = TFT_HEIGHT - y;
      break;
    case 3:
      rx = y;
      ry = TFT_WIDTH - x;
      break;
    default:
      rx = x;
      ry = y;
      break;
  }
  setblock(rx, rx, ry, ry);
  */
  setblock(x, x, y, y);
  writedat16(color);
  SPI.endTransaction();
}

void ili9328SPI::setRotation(uint8_t x){
    Adafruit_GFX::setRotation(x);
    rotation = x;
}

uint16_t ili9328SPI::color565(uint8_t r, uint8_t g, uint8_t b) {
  uint16_t rb, gb, bb;
  rb = (r & 0xF8) << 8;
  gb = (g & 0xFC) << 3;
  bb = b >> 3;
  return rb | gb | bb;
}

void ili9328SPI::setblock(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1)
{
  writecom16(0x0050);
  writedat16(y0);
  writecom16(0x0051);
  writedat16(y1);
  writecom16(0x0052);
  writedat16(x0);
  writecom16(0x0053);
  writedat16(x1);
  writecom16(0x0020);
  writedat16(x0);
  writecom16(0x0021);
  writedat16(y0);
  writecom16(0x0022);
}
void ili9328SPI::writereg16(uint16_t com, uint16_t dat)
{
  SPI.beginTransaction(setting);
  writecom16(com);
  writedat16(dat);
  SPI.endTransaction();
}
void ili9328SPI::writecom16(uint16_t com)
{
  CS_LOW;

  WRITE16(0x70);
  WRITE16(com >> 8);
  WRITE16(com);
  
  CS_HIGH;
}
void ili9328SPI::writedat16(uint16_t dat)
{
  CS_LOW;

  WRITE16(0x72);
  WRITE16(dat >> 8);
  WRITE16(dat);
  
  CS_HIGH;
}
