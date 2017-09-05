#ifndef _ILI9328_SPI_H
#define _ILI9328_SPI_H

#include "Arduino.h"

#include <Adafruit_GFX.h>
#include <SPI.h>

#define TFT_WIDTH 320
#define TFT_HEIGHT 240

#define CS_HIGH (*CSPort |= CSPinSet)
#define CS_LOW (*CSPort &= ~CSPinSet)
#define WRITE16(d) SPI.transfer(d)

class ili9328SPI : public Adafruit_GFX {

public:

  ili9328SPI(uint8_t cs, uint8_t reset);

  void     begin();
  void     drawPixel(int16_t x, int16_t y, uint16_t color);
  void     fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c);
  void     drawFastHLine(int16_t x0, int16_t y0, int16_t w, uint16_t color);
  void     drawFastVLine(int16_t x0, int16_t y0, int16_t h, uint16_t color);
  void     setRotation(uint8_t x);
  uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

  private:

  void     setblock(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1);
  void     writereg16(uint16_t com, uint16_t dat);
  void     writecom16(uint16_t com);
  void     writedat16(uint16_t dat);
  void     init();

#if defined(ESP8266) || defined(ESP32)
     uint8_t CSpin, RSTpin, rotation;
     uint32_t CSPinSet;
    volatile uint32_t *CSPort;
#else
  uint8_t CSpin, RSTpin, rotation;
  uint8_t CSPinSet;
  volatile uint8_t *CSPort;
#endif
  };
#endif // _ILI9328_SPI_H
