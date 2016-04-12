#include <EEPROM.h>
#include <Wire.h>
#include "uarm_library.h"
#include <Servo.h>


void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);
  uarm.pumpOn();
  uarm.setup();
}

void loop() {
  delay(5000);
  uarm.moveTo(-30,-10,10);
  uarm.moveToGround();
  delay(1000);
  uarm.moveTo(60,0,0,1,3);
  delay(3000);
  exit(0);

}
