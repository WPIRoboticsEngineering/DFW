#include <DFW.h>
#include "MyRobot.h"

void teleop( long time,DFW & dfw) { // function definition
	Serial.print("\r\nTeleop time remaining: ");
	Serial.print(time);
	Serial.print("\tright joystick: ");
	Serial.print(dfw.joystickrv());
	Serial.print("\tleft joystick: ");
	Serial.print(dfw.joysticklv());
	//Run functions in the robot class
	getArm().moveTo(35);
}
