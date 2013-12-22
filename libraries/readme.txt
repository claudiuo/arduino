For information on installing libraries, see: http://arduino.cc/en/Guide/Libraries

12/21/13
RGBLed library:
- downloaded from https://github.com/citrus/RGBLed
- installed
- to modify it to work with Arduino 1.0, change RGBLed.h and RGBLed.cpp line
  #include "WProgram.h"
with
  #if defined(ARDUINO) && ARDUINO >= 100 //check if using Arduino or Wiring
    #include "Arduino.h"
  #else
    #include "WProgram.h"
  #endif

RGBlink library:
- downloaded from https://github.com/l3kn/RGBlink
- not installed, does more than I need

