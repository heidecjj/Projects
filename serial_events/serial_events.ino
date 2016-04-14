#include <EEPROM.h>
#include <Wire.h>
#include "uarm_library.h"
#include <Servo.h>

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  uarm.setup();
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  serialEvent(); //call the function
           // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    if(inputString=="q") exit(0);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
  uarm.moveTo(.01, -21, 20);
  uarm.moveToGround();
  uarm.pumpOn();
  uarm.moveTo(.01, -21, 20);
  uarm.moveTo(-19, 0, 25);
  uarm.pumpOff();

}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      inputString.replace("\n","");
    }
  }
  
}
