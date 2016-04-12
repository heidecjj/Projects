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
  uarm.detachAll();
  uarm.setup();
  Serial.println("start");
}

void loop() {
  btn4=digitalRead(BTN_D4);
  btn7=digitalRead(BTN_D7);
  uarm.calXYZ();
  x = uarm.getCalX();  // assign robot x - axis coordinate to value x
  y = uarm.getCalY();
  z = uarm.getCalZ();
  
  // print x,y,z into command console 
  Serial.print("The current location is ");
  Serial.print(x);
  Serial.print(" , ");
  Serial.print(y);
  Serial.print(" , ");
  Serial.print(z);
  Serial.println();

  if(btn4==0){
    uarm.pumpOn();
  }else if(btn7==0){
    uarm.pumpOff();
  }
  delay(500);
}
