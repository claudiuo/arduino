/*
Adafruit Arduino - Lesson 3. RGB LED
*/

int redPin = 9;
int greenPin = 10;
int bluePin = 11;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}

void loop()
{
  setColor(255, 0, 0);  // red
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 255);  // blue
  delay(1000);
  setColor(255, 255, 0);  // yellow
  delay(1000);  
  setColor(80, 0, 80);  // purple
  delay(1000);
  setColor(0, 255, 255);  // aqua
  delay(1000);
  setColor(255, 165, 0);  // orange: FFA500
  delay(1000);
  setColor(255, 192, 203);  // pink: FFC0CB
  delay(1000);
  setColor(189, 255, 33);  // some kind of color: BDFF21
  delay(1000);
  setColor(0xFF, 0xF8, 0xDC);  // some kind of white: Cornsilk: FFF8DC
  delay(1000);
  setColor(0x4B, 0x0, 0x82);  // indigo
  delay(1000);
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
