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

1/6/14
- downloaded Android ADK library from https://github.com/felis/USB_Host_Shield_2.0 -developed by Oleg Mazurov see linked article here http://www.circuitsathome.com/mcu/programming/android_adk_compatible_usb_host_library_release
- downloaded android accessory source code as per http://developer.android.com/tools/adk/adk2.html#src-download
- copied the <adk-source-download>/adk2012/board/library/ADK2 directory and its contents into your sketchbook/libraries/ directory, so that you create a sketchbook/libraries/ADK2 directory.

1/9/14
- downloaded the Visualight library (included in visualight-1.1.zip) from https://github.com/lpercifield/visualight/releases/tag/1.1
- downloaded Android ADK libraries (adk_release_20120606.zip) and extracted libraries AndroidAccessory and USB_Host_Shield - tried a quick sketch but it didn't compile: I remember someone saying the USB_Host_Shield library from Google is invalid so I renamed the library USB_Host_Shield_Google
- downloaded then USB_Host_Shield-master.zip from https://github.com/felis/USB_Host_Shield/tree/master (first I got the dev version but that is not Arduino 1.0 ready so I deleted it) - unzipped and renamed USB_Host_Shield_master_10_felis to remember where it came from: got the same simple sketch (named adk_demokit_10) and compiled it without problems

2/2/14
- moved Ethernet library from /usr/share/arduino/libraries to this folder
- updated code so Multicast UDP works per https://github.com/TheThingSystem/steward/tree/master/things/examples/arduino
- in the future installing a new Arduino version with a new Ethernet library may break this -> remember to test!

2/2/14
- moved DHT library from the old /home/tavi/Dropbox/arduino/Libraries folder

2/5/14
- downloaded RCswitch library needed for radio boards, from https://code.google.com/p/rc-switch/downloads/detail?name=RCswitch_2.51.zip&can=2&q=

2/19/14
- moved NinjaEthernet and TimedAction libraries from the old /home/tavi/Dropbox/arduino/Libraries folder

4/3/14
- added DigiPixel library downloaded 4/3/14 from https://github.com/bradsprojects/DigiPixel

8/9/14
- downloaded and added virtual wire library from https://www.pjrc.com/teensy/td_libs_VirtualWire.html needed by this instructable: 
http://www.instructables.com/id/ARDUINO-WIRELESS-HOME-SECURITY-SYSTEM. Interesting: this library has support for Teensy as well.
