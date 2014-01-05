/*
  smARtMOD LED 5TO5D Basic Blink.
  
  Blinks all 5 LEDs on the 5TO5D (SMRTM502).

  Parts used:
  5to5d (SMRTM502)
  SmartCore U (SMRTC002)
  smARtBUS Basic Double (SMRTB104)

   Created by: Joseph Stackhouse (joseph.stackhouse@stack-tech.com)
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

// The setup routine runs once when you press reset:
void setup() {                
  // Initialize the digital pins as an outputs.
    for (int x=0; x<5; x++) {
    pinMode(ledPin[x], OUTPUT); }
}

// The loop routine runs over and over again forever:
void loop() {
  // Turn on all LEDs (HIGH is the voltage level)
  for (int x=0; x<5; x++) {
    digitalWrite(ledPin[x], HIGH); 
  } 
  
  delay(500);               // Wait half a second.

  // Turn the LEDs off by making the voltage LOW
  for (int x=0; x<5; x++) { 
    digitalWrite(ledPin[x], LOW); 
  } 

  delay(500);               // Wait half a second.
}
