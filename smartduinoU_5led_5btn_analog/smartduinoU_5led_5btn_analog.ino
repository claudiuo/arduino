/*
  Based on smARtMOD LED 5TO5D Basic Blink by Joseph Stackhouse (joseph.stackhouse@stack-tech.com)
  
  Added 5A5 button module: each button turn an LED on/off.  
  
  Parts used:
  5to5d (SMRTM502)
  5A5 button (SMRTM503)
  SmartCore U (SMRTC002)
  smARtBUS Basic Double (SMRTB104)
  smARtBUS Basic Replicator Vertical (SMRTB111)

  Modified by ClaudiuO: https://github.com/claudiuo
 */
 
//Declare array for LEDs
byte ledPin[] = {2, 3, 4, 5, 6};
/*
[Location]   [PCB Print]   [Digital PIN]
----------------------------------------
Center          #1               2
Top             #2               3
Left            #3               4
Bottom          #4               5
Right           #5               6
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

// declare array for button values
boolean btnState[5];

// The setup routine runs once when you press reset:
void setup() {                
  // Initialize the digital pins as an outputs
  // and the analog pins as inputs
  for (int x=0; x<5; x++) {
    pinMode(ledPin[x], OUTPUT);
    pinMode(btnPin[x], INPUT);     
  }
}

// The loop routine runs over and over again forever:
void loop() {
  // read the state of the pushbuttons
  for (int x=0; x<5; x++) {
    btnState[x] = digitalRead(btnPin[x]);
  }

  for (int x=0; x<5; x++) {
    if (btnState[x] == HIGH) {     
      // turn corresponding LED on
      digitalWrite(ledPin[x], HIGH);  
    } 
    else {
      // turn corresponding LED off
      digitalWrite(ledPin[x], LOW); 
    }
  }
}
