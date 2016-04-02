#include <EEPROM.h>
#include <Wire.h>
#include "uarm_library.h"
#include <Servo.h>


void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);
  uarm.init();
}

void loop() {
  uarm.moveTo(1,-21,20);
  uarm.pumpOn();
  uarm.moveToGround();
  uarm.moveTo(1,-21,20);
  uarm.moveTo(-19,0,25);
  uarm.pumpOff();

}
