#include <EEPROM.h>
#include <Wire.h>
#include "uarm_library.h"
#include <Servo.h>


int x;
int y;
int z;
int btn4;
int btn7;

int num1;
int num2;
int integerValue;
byte incomingByte;
boolean mySwitch = true;
boolean go = false;

void setup() {
 
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial port at 9600 bps
  uarm.init();
  uarm.moveTo(0.1,-15,20);
}

void loop() {
  uarm.moveToGround();
  exit(0);
}
