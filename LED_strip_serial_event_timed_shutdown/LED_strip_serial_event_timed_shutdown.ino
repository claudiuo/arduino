/*
  Turn on a LED strip based on the values read from Serial.

  Uses SerialEvent to wake up and light the strip.

  Uses TimerOne library with timer set to the max overflow time: 8388; see http://playground.arduino.cc/Code/Timer1
  To achieve longer intervals, let the timer interrupt fire several times. When desired interval reached,
  turn off LED strip, if no serial events happen; when new serial event happens, timer is restarted.
*/
#include <TimerOne.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
// there are 30 pixels but for some reason I noticed that 3 of them are used for each command
// for example, pixels.setPixelColor(0, firstPixelColor); sets 3 pixels not just one
// I assume this is because of a cheap LED strip in which each 3 LEDs are grouped together
// until I find a solution (if any), treat the strip as having 10 LEDs
#define NUMPIXELS 10

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ400);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
// use volatile for shared variables
volatile unsigned long now = 0;

boolean doneReading = false;
int type, fail, success, skip = 0;

unsigned long timerPeriod = 0.2 * 60 * 1000 * 1000;    // high value to overflow timer at 8388 ms
unsigned long timerInterval = 1.0 * 60 * 1000;    // min in millis

void myHandler() {
  // just a debug message
  Serial.print("in the interrupt handler. timer started ");
  Serial.print(millis() - now);
  Serial.println(" ms ago");

  if ((millis() - now) > timerInterval) {
    Serial.println("stop the timer");
    // stop the timer
    Timer1.stop();

    // turn off the LEDs
    // todo: send the correct values: for now, all are off
    setSameColorLEDs(100,0,0);
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    type = Serial.parseInt();
    fail = Serial.parseInt();
    success = Serial.parseInt();
    skip = Serial.parseInt();

    if (Serial.read() == '\n') {
      doneReading = true;
    }
  }
}

void setup() {
  Serial.begin(9600);

  now = millis();
  Timer1.initialize(timerPeriod);
  Timer1.attachInterrupt(myHandler);

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show(); // Initialize all pixels to 'off'
}

void loop() {
  // to read a variable which the interrupt code writes, we
  // must temporarily disable interrupts, to be sure it will
  // not change while we are reading.  To minimize the time
  // with interrupts off, just quickly make a copy, and then
  // use the copy while allowing the interrupt to keep working.
  // TODO if needed
  //  noInterrupts();
  //  blinkCopy = blinkCount;
  //  interrupts();

  // turn on the LEDs when a newline arrives
  if (doneReading) {

    Serial.println("got all values. turning on LEDs. restarting timer");

    // turn on the LEDs
    // todo: send the correct values: for now, first is purple, rest are red, blue, green in order
    turnOnLEDs(pixels.Color(255,255,0),5,6,7);

    // clear the variables
    type, fail, success, skip = 0;
    doneReading = false;

    // restart the timer so the LEDs stay on for some time
    // reset now to start a new full interval
    now = millis();
    Timer1.resume();
  }
}

void turnOnLEDs(uint32_t firstPixelColor, int howManyRed, int howManyBlue, int howManyGreen) {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  // first pixel has the color based on first 3 args
  pixels.setPixelColor(0, firstPixelColor);

  // todo: check the rest of args added up don't go over NUMPIXELS-1;
  // even if we do, not a problem going over, they just won't light up

  // light as many LEDs of each color as needed
  for (uint16_t i = 1; i <= howManyRed; i++) {
    Serial.print("red: ");
    Serial.println(i);
    // pixels.Color takes RBG values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(150, 0, 0));
  }
  for (uint16_t i = howManyRed+1; i <= howManyRed+howManyBlue; i++) {
    Serial.print("blue: ");
    Serial.println(i);
    // pixels.Color takes RBG values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
  }
  for (uint16_t i = howManyRed+howManyBlue+1; i <= howManyRed+howManyBlue+howManyGreen; i++) {
    Serial.print("green: ");
    Serial.println(i);
    // pixels.Color takes RBG values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(50);
}

void setSameColorLEDs(int red, int blue, int green) {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for (uint16_t i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RBG values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(red, blue, green));
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  delay(50);
}

