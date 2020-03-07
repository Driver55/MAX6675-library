// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#ifndef __MAX6675__
#define __MAX6675__

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class MAX6675 {
 public:
  MAX6675(int8_t SCLK, int8_t CS, int8_t MISO);

  double readCelsius(void);
  int    readTenthsOfCelsius(void);
  double readFahrenheit(void);
  // For compatibility with older versions:
  double readFarenheit(void) { return readFahrenheit(); }
 
 private:
  int8_t sclk, miso, cs;
  uint8_t spiread(void);
};

#endif  //__MAX6675__