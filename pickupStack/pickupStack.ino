#include <EEPROM.h>
#include <Wire.h>
#include "uarm_library.h"
#include <Servo.h>


void setup() {
  uarm.setup();
}

void loop() {
  uarm.moveTo(1,-21,20);
  uarm.pumpOn();
  uarm.moveToGround();
  uarm.moveTo(1,-21,20);
  uarm.moveTo(-19,0,25);
  uarm.pumpOff();

}
