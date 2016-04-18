#include <EEPROM.h>
#include <Wire.h>
#include "uarm_library.h"
#include <Servo.h>

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  uarm.setup();
  // reserve 200 bytes for the inputString:
}

void loop() {
  // put your main code here, to run repeatedly:
  uarm.moveTo(0.01,-10,10);
  delay(1000);
  uarm.moveTo(0.01,-29,8);
}
