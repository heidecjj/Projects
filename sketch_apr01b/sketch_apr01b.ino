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
  pinMode(BTN_D4,INPUT_PULLUP);
  pinMode(BTN_D7,INPUT_PULLUP);
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial port at 9600 bps
  uarm.moveTo(0,-10,10);
  uarm.init();
  Serial.println("start");
}

void loop() {
  uarm.moveTo(0,-25,21);
  uarm.moveTo(0,-29,3);
  uarm.pumpOn();
  delay(1000);
  uarm.moveTo(0,0,10,1,.5);
  uarm.moveTo(-24,-3,23);
  delay(200);
  uarm.pumpOff();
  delay(500);
}
