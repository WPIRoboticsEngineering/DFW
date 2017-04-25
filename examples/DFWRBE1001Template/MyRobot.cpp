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
	while (true) {
		int error = position - analogRead(potPin);
		motor.write(90 + error / 5);
		if (abs(error) < 20) break;
	}
	motor.write(90);
}
void Arm::robotShutdownFunction(void){
	Serial.println("Here is where I shut down my robot code");
}
