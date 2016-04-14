#include <EEPROM.h>
#include <Wire.h>
#include "uarm_library.h"
#include <Servo.h>


void setup() {
  uarm.setup();
}

void loop() {
  uarm.moveTo(.01,-21,20);
  uarm.moveToGround();
  uarm.pumpOn();
  uarm.moveTo(.01,-21,20);
  uarm.moveTo(-19,0,25);
  uarm.pumpOff();

}
