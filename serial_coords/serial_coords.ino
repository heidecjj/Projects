#include <EEPROM.h>
#include <Wire.h>
#include "uarm_library.h"
#include <Servo.h>

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int x;

void setup() {
  uarm.setup();
  
  //reserve 200 bytes for the inputString:
  inputString.reserve(100);
  /*Serial.print("all commands must be enclosed in parenthesis\n"
	  "commands can be sent sequentially in the same line\n"
	  "ex: (command)(command)(command)\n"
	  "type (help) for a list of commands\n");*/
}

void loop() {
	delay(50);//required delay to stop breakage
  if (serialEvent()) {
    Serial.println(">>"+inputString);
    goToCoord(inputString);
    // clear the string:
    inputString = "";
  }
}


boolean serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
	
    // add it to the inputString:
    inputString += inChar;
	
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar=='\n') {
		inputString.replace("\n","");
		return true;
    }
  }
}


void goToCoord(String commandsString) {
	//size of following arrays
	int arraySize = 0;

	//counts number of commandsString
	for (int i = 0; i < commandsString.length(); i++) {
		if (commandsString[i] == '(') arraySize++;
	}

	//holds start and end of each command in the input string
	int splitIndices[arraySize][2];
	//marks the index of '(' as a start and ')' as the end
	int j=0; //counter for each command
	for (int i = 0; i < commandsString.length(); i++) {
		if (commandsString[i]=='(') splitIndices[j][0] = i;
		if (commandsString[i] == ')') {
			splitIndices[j][1] = i;
			j++;
		}
	}

	//holds each coordinate as a string ie "(10,-25.3,6)"
	String commands[arraySize];
	for (int i = 0; i < arraySize; i++) {
		commands[i] = commandsString.substring(splitIndices[i][0], splitIndices[i][1]);
		commands[i].replace("(", "");
	}

	double coordXYZ[arraySize][4];
	for (int i = 0; i < arraySize; i++) {
		int comma1 = -1;
		int comma2 = -1;
		int comma3 = -1;
		for (int k = 0; k < commands[i].length(); k++) {
			if (commands[i].charAt(k) == ',') {
				if (comma1 <0) comma1 = k;
				else if(comma2<0) comma2 = k;
				else comma3 = k;
			}
		}

		if (comma1 >= 0 && comma2 >= 0&&comma3<0) {
			coordXYZ[i][0] = MOVETO;
			coordXYZ[i][1] = (double)(commands[i].substring(0, comma1)).toFloat();
			coordXYZ[i][2] = (double)(commands[i].substring(comma1+1,comma2)).toFloat();
			coordXYZ[i][3] = (double)(commands[i].substring(comma2+1)).toFloat();

		} else if (comma1 >= 0 && comma2 >= 0 && comma3>=0) {
			coordXYZ[i][0] = (double)(commands[i].substring(0, comma1)).toFloat();
			coordXYZ[i][1] = (double)(commands[i].substring(comma1 + 1, comma2)).toFloat();
			coordXYZ[i][2] = (double)(commands[i].substring(comma2 + 1,comma3)).toFloat();
			coordXYZ[i][3] = (double)(commands[i].substring(comma3 + 1)).toFloat();
		}
		else if (comma1<0&&comma2<0&&comma3<0) {
			if(commands[i].equalsIgnoreCase("g")) coordXYZ[i][0] = MOVETO_GROUND;
			else if (commands[i].equalsIgnoreCase("n")) coordXYZ[i][0] = PUMP_ON;
			else if (commands[i].equalsIgnoreCase("f")) coordXYZ[i][0] = PUMP_OFF;
			else if (commands[i].equalsIgnoreCase("a")) coordXYZ[i][0] = ALARM;
			else if (commands[i].equalsIgnoreCase("help")) coordXYZ[i][0] = HELP;
			else if (commands[i].equalsIgnoreCase("d")) coordXYZ[i][0] = DETACH_ALL;
			//else if (commands[i].equalsIgnoreCase("l")) coordXYZ[i][0] = GET_LOCATION;
		}
		
	}

	for (int i = 0; i < arraySize; i++) {
		if (coordXYZ[i][0] == MOVETO) {
			uarm.moveTo(coordXYZ[i][1], coordXYZ[i][2], coordXYZ[i][3]);
			//Serial.println("Moved to: (" + (String)(uarm.getCalX()) + "," + (String)(uarm.getCalY()) + "," + (String)(uarm.getCalZ()) + ")");
		}
		else if (coordXYZ[i][0] == MOVETO_RELATIVE) {
			uarm.moveTo(coordXYZ[i][1], coordXYZ[i][2], coordXYZ[i][3],RELATIVE,1);
			//Serial.println("Moved to: (" + (String)(uarm.getCalX()) + "," + (String)(uarm.getCalY()) + "," + (String)(uarm.getCalZ()) + ")");
		}
		else if (coordXYZ[i][0] == MOVETO_GROUND) {
			uarm.moveToGround();
			//uarm.detachAll(); 
			//Serial.println("Moved to: (" + (String)(uarm.getCalX()) + "," + (String)(uarm.getCalY()) + "," + (String)(uarm.getCalZ()) + ")");
		}else if (coordXYZ[i][0] == PUMP_ON) {
			uarm.pumpOn();
			Serial.println("Pump On");
		}else if (coordXYZ[i][0] == PUMP_OFF) {
			uarm.pumpOff();
			Serial.println("Pump Off");
		}else if (coordXYZ[i][0] == ALARM) {
			uarm.alert(10,20,10);
			Serial.println("Alarm");
		}else if (coordXYZ[i][0] == HELP) {
			Serial.println("(x,y,z) moves to coordinate (x,y,z)");
			Serial.println("(0,x,y,z) moves to coordinate (x,y,z)");
			Serial.println("(1,x,y,z) moves by (x,y,z) in their respective directions");
			Serial.println("(g) moves to ground");
			Serial.println("(n) turns on pump");
			Serial.println("(f) turns off pump");
			Serial.println("(a) sounds alarm");
			Serial.println("(d) detaches all servos");
			Serial.println("(l) gets the current location of the arm");
		}else if (coordXYZ[i][0] == DETACH_ALL) {
			uarm.detachAll();
			Serial.println("Detach all");
		}/*else if (coordXYZ[i][0] == GET_LOCATION) {
			uarm.calXYZ();
			Serial.println("Location: (" + (String)(uarm.getCalX()) + "," + (String)(uarm.getCalY()) + "," + (String)(uarm.getCalZ()) + ")");
		}*/

	}
	

}
