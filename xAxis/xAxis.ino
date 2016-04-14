#include <EEPROM.h>
#include <Wire.h>
#include "uarm_library.h"
#include "uarm_calibration.h"
#include <Servo.h>

void setup() {
  uarm.setup();
}

void loop() {

  
  uarm.moveTo(0.01,-10,8);
  delay(5000);
  uarm.moveTo(0.01,-30,8);
  exit(0);
}
