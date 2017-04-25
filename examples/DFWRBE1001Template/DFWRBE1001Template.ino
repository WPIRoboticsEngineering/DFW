/* This is the RBE 1001 Template as of
 *
 * 3/28/17
 *
 * This Template
 * is designed to run the autonomous and teleop sections of the final
 * competition. Write and test your autonomous and teleop code on your
 * own and place the code in auto.cpp or teleop.cpp respectively.
 * The functions will be called by the competition framework based on the
 * time and start button. DO NOT change this file, your code will be called
 * by the framework. The framework will pass your code a reference to the DFW
 * object as well as the amount of MS remaining.
 */
#include <DFW.h>
#include "MyRobot.h"

int ledpindebug = 13; //Wireless controller Debug pin. If lit then there is no communication.
DFW dfw(ledpindebug, autonomous, teleop,robotShutdown); // Instantiates the DFW object and setting the debug pin. The debug pin will be set high if no communication is seen after 2 seconds
Arm myArm;
void setup() {
	Serial.begin(9600); // Serial output begin. Only needed for debug
	dfw.begin(); // Serial1 output begin for DFW library. Buad and port #."Serial1 only"
	myArm.initialize(1,2);
}
void loop() {
	dfw.run();
}

void robotShutdown(void){
	// this function shuts down your robot
	myArm.robotShutdownFunction();
}
Arm getArm(){
	return myArm;
}
