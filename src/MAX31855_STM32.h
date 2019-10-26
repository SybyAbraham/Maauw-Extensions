/*************************************************** 
  This is a library for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#ifndef MAX31855_STM32_H
#define MAX31855_STM32_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class MAX31855_STM32 {
 public:
  MAX31855_STM32(int8_t _sclk, int8_t _cs, int8_t _miso);
  MAX31855_STM32(int8_t _cs);

  void begin(void);
  double readInternal(void);
  double readCelsius(void);
  double readFarenheit(void);
  uint8_t readError();

 private:
  boolean initialized;

  int8_t sclk, miso, cs;
  uint32_t spiread32(void);
};

#endif
