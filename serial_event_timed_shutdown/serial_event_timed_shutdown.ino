/*
  Turn on a LED strip based on the values read from Serial.
  
  Uses SerialEvent to wake up and light the strip.
  
  Uses TimerOne library with timer set to the max overflow time: 8388; see http://playground.arduino.cc/Code/Timer1
  To achieve longer intervals, let the timer interrupt fire several times. When desired interval reached,
  turn off LED strip, if no serial events happen; when new serial event happens, timer is restarted.
*/
#include <TimerOne.h>

// use volatile for shared variables
volatile unsigned long now = 0;

boolean doneReading = false;
int type, fail, success, skip = 0;

unsigned long timerPeriod = 0.2 * 60 * 1000 * 1000;    // min in micros
unsigned long timerInterval = 1.0 * 60 * 1000;    // min in millis

void myHandler() {
    // just a debug message
    Serial.print("in the interrupt handler. timer started ");
    Serial.print(millis() - now);
    Serial.println(" ms ago");

    if((millis() - now) > timerInterval) {
        Serial.println("stop the timer");
        // stop the timer
        Timer1.stop();

        // todo: turn off the LEDs
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

    pinMode(LED_BUILTIN, OUTPUT);
    // set to LOW to make it obvious when it becomes HIGH in the interrupt handler
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off

    now = millis();
    Timer1.initialize(timerPeriod);
    Timer1.attachInterrupt(myHandler);
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
    
//    Serial.print(doneReading);

  // turn on the LEDs when a newline arrives
  if (doneReading) {

    Serial.println("got all values. blinking led. restarting timer");

    // todo: turn on the LEDs

    // clear the variables
    type, fail, success, skip = 0;
    doneReading = false;

    // restart the timer so the LEDs stay on for some time
    // reset now to start a new full interval
    now = millis();
    Timer1.resume();
  }
}
