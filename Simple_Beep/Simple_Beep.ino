#include <EEPROM.h>
#include <Wire.h>
#include "uarm_library.h"
#include <Servo.h>


void setup() {
  // put your setup code here, to run once:
  uarm.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  uarm.alert(10,10,10);
  exit(0);
}
