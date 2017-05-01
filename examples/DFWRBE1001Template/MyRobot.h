#pragma once

#include "Servo.h"

class Arm {
private:
	unsigned potPin;
	Servo motor;
public:
	void initialize(unsigned armMotorPin, unsigned armPotPin);
	void moveTo(unsigned position);
	void robotShutdownFunction(void);

};

Arm * getArm();
