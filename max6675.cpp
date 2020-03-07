// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif
#include <util/delay.h>
#include <stdlib.h>
#include "max6675.h"

MAX6675::MAX6675(int8_t SCLK, int8_t CS, int8_t MISO) {
  sclk = SCLK;
  cs = CS;
  miso = MISO;

  //define pin modes
  pinMode(cs, OUTPUT);
  pinMode(sclk, OUTPUT); 
  pinMode(miso, INPUT);

  digitalWrite(cs, HIGH);
}

/**
	Returns a temperature in Celsius
	~130 times faster.
	@return temperature in degree Celsius
*/
double MAX6675::readCelsius(void) {

  uint16_t v;

  digitalWrite(cs, LOW);
  delayMicroseconds(1);
  v = spiread();
  v <<= 8;
  v |= spiread();

  digitalWrite(cs, HIGH);

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return NAN; 
    //return -100;
  }

  v >>= 3;

  return v*0.25;
}

/**
	Returns a temperature in Celsius
	~130 times faster.
	@return temperature in tenths of degree Celsius
*/
int MAX6675::readTenthsOfCelsius() {
	double x = readCelsius();
	int z = (int) (x * 10);
	return z;

}

double MAX6675::readFahrenheit(void) {
  return readCelsius() * 9.0/5.0 + 32;
}

/**
	Read 1 byte from SW SPI ~130 times faster.
	@return 1 byte
*/
byte MAX6675::spiread(void) { 
  int i;
  byte d = 0;

  for (i=7; i>=0; i--)
  {
    digitalWrite(sclk, LOW);
    
	delayMicroseconds(1);
    if (digitalRead(miso)) {
      //set the bit to 0 no matter what
      d |= (1 << i);
    }

    digitalWrite(sclk, HIGH);
    delayMicroseconds(1);
  }

  return d;
}
