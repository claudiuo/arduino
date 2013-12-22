/*

 CheerLights!
 
 CheerLights Channel --> Arduino Ethernet --> RGB led
 
 This sketch subscribes to the CheerLights ThingSpeak Channel and relays the
 last command from the Internet to an RGB led (from Evil Mad Scientist). This
 sketch uses DHCP to obtain an IP address automatically and requires Arduino 1.0.
 
 Arduino Requirements:
 
   * Arduino Ethernet (or Arduino + Ethernet Shield)
   * Arduino 1.0 IDE

     http://www.digitalmisery.com/wp-content/uploads/2011/11/GEColorEffects-Arduino-1.0.zip
   
 Network Requirements:

   * Ethernet port on Router    
   * DHCP enabled on Router
   * Unique MAC Address for Arduino

 Getting a Globally Unique MAC Address from ThingSpeak:
 
   * Sign Up for New User Account - https://www.thingspeak.com/users/new
   * Register your Arduino by selecting Devices, Add New Device
   * Once the Arduino is registered, click Generate Unique MAC Address
   * Enter the new MAC Address in this sketch under "Local Network Settings"
 
 Created: Novemeber 29, 2011 by Hans Scharler - http://www.iamshadowlord.com
 
 Additional Credits:
 http://www.digitalmisery.com
 http://www.deepdarc.com
 
 To join the CheerLights project, visit http://www.cheerlights.com
 
*/

#include <SPI.h>
#include <Ethernet.h>

// these are the colors supported by CheerLights
const int COLOR_WHITE = 0;
const int COLOR_BLACK = 1;
const int COLOR_RED = 2;
const int COLOR_GREEN = 3;
const int COLOR_BLUE = 4;
const int COLOR_CYAN = 5;
const int COLOR_MAGENTA = 6;
const int COLOR_YELLOW = 7;
const int COLOR_PURPLE = 8;
const int COLOR_ORANGE = 9;
const int COLOR_WARMWHITE = 10;
const int COLOR_PINK = 11; // pink added to CheerLights 12/20/13

// RGB led Setup
int redPin = 10;
int greenPin = 3;
int bluePin = 5;

static uint16_t c;

// Local Network Settings
byte mac[] = { 0xD4, 0x28, 0xB2, 0xFF, 0x50, 0xA2 }; // Must be unique on local network

// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String thingSpeakChannel = "1417";                // Channel number of the CheerLights Channel
String thingSpeakField = "1";                     // Field number of the CheerLights commands 
const int thingSpeakInterval = 16 * 1000;      // Time interval in milliseconds to get data from ThingSpeak (number of seconds * 1000 = interval)

// Variable Setup
long lastConnectionTime = 0; 
String lastCommand = "";
boolean lastConnected = false;
int failedCounter = 0;

// Initialize Arduino Ethernet Client
EthernetClient client;

void setup() {
  // Setup Serial
  Serial.begin(9600);
  delay(100);
  
  Serial.flush();
  delay(100);
  
  // test the led
  testLeds(500);
  
  // Start Ethernet on Arduino
  startEthernet();
}

void loop() {
   
  // Process CheerLights Commands
  if(client.available() > 0)
  {  
    delay(100); 
    
    String response;
    char charIn;

    do {
        charIn = client.read(); // read a char from the buffer
        response += charIn; // append that char to the string response
      } while (client.available() > 0); 
          
    // Send matching commands to the RGB led
    if (response.indexOf("white") > 0)
    {  
        lastCommand = "white";
        ledColor(COLOR_WHITE);
    }
    else if (response.indexOf("black") > 0)
    {  
        lastCommand = "black";
        ledColor(COLOR_BLACK);
    }
    else if (response.indexOf("red") > 0)
    {  
        lastCommand = "red";
        ledColor(COLOR_RED);
    }
    else if (response.indexOf("green") > 0)
    {  
        lastCommand = "green";
        ledColor(COLOR_GREEN);
    }
    else if (response.indexOf("blue") > 0)
    {  
        lastCommand = "blue";
        ledColor(COLOR_BLUE);
    }
    else if (response.indexOf("cyan") > 0)
    {  
        lastCommand = "cyan";
        ledColor(COLOR_CYAN);
    }
    else if (response.indexOf("magenta") > 0)
    {  
        lastCommand = "magenta";
        ledColor(COLOR_MAGENTA);
    }
    else if (response.indexOf("yellow") > 0)
    {  
        lastCommand = "yellow";
        ledColor(COLOR_YELLOW);
    }
    else if (response.indexOf("purple") > 0)
    {  
        lastCommand = "purple";
        ledColor(COLOR_PURPLE);
    }
    else if (response.indexOf("orange") > 0)
    {  
        lastCommand = "orange";
        ledColor(COLOR_ORANGE);
    }
    else if (response.indexOf("warmwhite") > 0)
    {  
        lastCommand = "warmwhite";
        ledColor(COLOR_WARMWHITE);
    }
    else if (response.indexOf("pink") > 0)
    {  
        lastCommand = "pink";
        ledColor(COLOR_PINK);
    }
    else
    {
        //Serial.println(response);
        lastCommand = "(no match)";
        ledColor(-1);
    }

    // Echo command
    delay(200);
    Serial.println("CheerLight Command Received: "+lastCommand);
    Serial.println();
    delay(200); 
    
  }
  
    // Disconnect from ThingSpeak
  if (!client.connected() && lastConnected)
  {
    Serial.println("...disconnected");
    Serial.println();
    
    client.stop();
  }
  
  // Subscribe to ThingSpeak Channel and Field
  if(!client.connected() && (millis() - lastConnectionTime > thingSpeakInterval))
  {
    subscribeToThingSpeak(thingSpeakChannel, thingSpeakField);
  }
  
  // Check if Arduino Ethernet needs to be restarted
  if (failedCounter > 3 ) {startEthernet();}
  
  lastConnected = client.connected();
  
} // End loop

void subscribeToThingSpeak(String tsChannel, String tsField)
{
  if (client.connect(thingSpeakAddress, 80))
  {         
    Serial.println("Connecting to ThingSpeak...");
    Serial.println();
      
    failedCounter = 0;
    
    client.println("GET /channels/"+tsChannel+"/field/"+tsField+"/last.txt HTTP/1.0");
    client.println();
    
    lastConnectionTime = millis();
  }
  else
  {
    failedCounter++;
    
    Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");   
    Serial.println();
    
    lastConnectionTime = millis(); 
  }
}

void startEthernet()
{
  
  client.stop();

  Serial.println("Connecting Arduino to network...");
  Serial.println();  

  delay(1000);
  
  // Connect to network amd obtain an IP address using DHCP
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("DHCP Failed, reset Arduino to try again");
    Serial.println();
  }
  else
  {
    Serial.println("Arduino connected to network using DHCP");
    Serial.println();
  }
  
  delay(1000);
}

void off()
{
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void ledColor(int color)
{
  switch (color) {
    case COLOR_WHITE:
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, HIGH);
      break;
    case COLOR_BLACK:
      // black is basically all leds off
      off();
      break;
    case COLOR_RED:
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
      break;
    case COLOR_GREEN:
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, LOW);
      break;
    case COLOR_BLUE:
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, HIGH);
      break;
    case COLOR_CYAN:
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, HIGH);
      break;
    case COLOR_MAGENTA:
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, HIGH);
      break;
    case COLOR_YELLOW:
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, LOW);
      break;
    case COLOR_PURPLE:
      off();  // clear all colors: may not be needed, seen problem when analogWrite is called after a digitalWrite
      analogWrite(redPin, 128);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 128);
      break;
    case COLOR_ORANGE:
      off();  // clear all colors: may not be needed, seen problem when analogWrite is called after a digitalWrite
      // color: FFA500
      analogWrite(redPin, 255);
      analogWrite(greenPin, 165);
      analogWrite(bluePin, 0);
      break;
    case COLOR_WARMWHITE:
      off();  // clear all colors: may not be needed, seen problem when analogWrite is called after a digitalWrite
      // color: Cornsilk - FFF8DC
      analogWrite(redPin, 255);
      analogWrite(greenPin, 248);
      analogWrite(bluePin, 220);
      break;
    case COLOR_PINK:
      off();  // clear all colors: may not be needed, seen problem when analogWrite is called after a digitalWrite
      // color: FFC0CB
      analogWrite(redPin, 255);
      analogWrite(greenPin, 192);
      analogWrite(bluePin, 203);
      break;
    default: 
      off();  // clear all colors: may not be needed, seen problem when analogWrite is called after a digitalWrite
      // show some kind of color just so we show something: BDFF21
      analogWrite(redPin, 189);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 33);
      break;
  }
}

void testLeds(int delayMs)
{
  ledColor(COLOR_RED);
  delay(delayMs);
  ledColor(COLOR_GREEN);
  delay(delayMs);
  ledColor(COLOR_BLUE);
  delay(delayMs);
  ledColor(COLOR_WHITE);
  delay(delayMs);
  ledColor(COLOR_CYAN);
  delay(delayMs);
  ledColor(COLOR_MAGENTA);
  delay(delayMs);
  ledColor(COLOR_YELLOW);
  delay(delayMs);
  ledColor(COLOR_PURPLE);
  delay(delayMs);
  ledColor(COLOR_ORANGE);
  delay(delayMs);
  ledColor(COLOR_WARMWHITE);
  delay(delayMs);
  ledColor(COLOR_PINK);
  delay(delayMs);
  ledColor(-1);
  delay(delayMs);
  off();
  delay(delayMs);
}
