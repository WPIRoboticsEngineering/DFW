#include "MyRobot.h"
#include "Arduino.h"
/**
 * THese are the execution runtions
 */
void Arm::initialize(unsigned armMotorPin, unsigned armPotPin) {
	potPin = armPotPin;
	pinMode(armMotorPin, INPUT);
	motor.attach(armMotorPin, 1000, 2000);
}

void Arm::moveTo(unsigned position) {
	motor.write(position);
}
void Arm::robotShutdownFunction(void){
	Serial.println("Here is where I shut down my robot code");
}
