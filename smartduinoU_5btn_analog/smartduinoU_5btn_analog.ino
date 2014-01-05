/*
  Based on Button created 2005 by DojoDave <http://www.0j0.org> modified 30 Aug 2011 by Tom Igoe

  Adapted for smartduino using the 5A5 button module: each button turns the LED on/off.
  
  Parts used:
  5A5 button (SMRTM503)
  SmartCore U (SMRTC002)
  smARtBUS Basic Double (SMRTB104)

  Modified by ClaudiuO: https://github.com/claudiuo
 */

// Declare array for buttons
byte btnPin[] = {A0, A1, A2, A3, A4};
/*
[Location]   [PCB Print]   [Analog PIN]
----------------------------------------
Center          #1               A0
Top             #2               A1
Left            #3               A2
Bottom          #4               A3
Right           #5               A4
*/

const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pins as inputs
  for (int x=0; x<5; x++) {
    pinMode(btnPin[x], INPUT);     
  }
}

void loop(){
  // read the state of the pushbuttons
  buttonState = 1;
  for (int x=0; x<5; x++) {
    buttonState = buttonState && digitalRead(btnPin[x]);
  }

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}

