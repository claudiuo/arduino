/**
 * Read a color from Serial and light up the DigiPixel according to this color.
 * In my case I am getting the color from a CheerLights node-red flow runnning
 * on a Raspberry Pi but it can even be entered manually in the Serial Monitor.
 *
 * Instead of coding different kind of behaviors on the Arduino, the sketch is
 * kept simple (keeps the last color on without turning it off) and if I want
 * to implement other patterns (like keep a color on only for 30 seconds, or
 * something else) I do it on the node-red side which gives me a lot more
 * flexibility without the need to recompile/upload new code to Arduino.
 *
 * Note: CheerLights has 4 more colors than DigiPixel so the extra ones are
 * mapped to existing DigiPixel colors in the getColor() function.
 */

#include <DigiPixel.h>

// leave the following line uncommented for use with a Digispark
//DigiPixel digiPixel(3,0,5,2,1);  // LED Latch/Button Shift !load pin, LED/Button clock pin, LED Data Pin, LED Output Enable pin, Buttons data pin)

// leave the following line uncommented for use with an Arduino
DigiPixel digiPixel(5,2,6,4,3);  // LED Latch/Button Shift !load pin, LED/Button clock pin, LED Data Pin, LED Output Enable pin, Buttons data pin)

char str[8];

void setup(){
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0) {
    memset(str,0,sizeof(str));
    Serial.readBytes(str, 8);
    Serial.print(str);
    byte color = getColor(str);
    Serial.print(color);
    digiPixel.fillScreen(color);
  }
  digiPixel.drawScreen();
}

byte getColor(String str) {
  // several CheerLights colors can be mapped directly to DigiPixel colors
  // in addition, CheerLights has 4 more colors"
  // warmwhite -> map to white
  // purple -> map to magenta
  // orange -> map to yellow
  // pink -> map to red
  
  if(str.equalsIgnoreCase("black")) return 0;
  else if(str.equalsIgnoreCase("red") || str.equalsIgnoreCase("pink")) return 1;
  else if(str.equalsIgnoreCase("green")) return 2;
  else if(str.equalsIgnoreCase("yellow") || str.equalsIgnoreCase("orange")) return 3;
  else if(str.equalsIgnoreCase("blue")) return 4;
  else if(str.equalsIgnoreCase("magenta") || str.equalsIgnoreCase("purple")) return 5;
  else if(str.equalsIgnoreCase("cyan")) return 6;
  else if(str.equalsIgnoreCase("white") || str.equalsIgnoreCase("warmwhite")) return 7;
  else return 0;
}
