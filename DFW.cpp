/* Serial controller library for DFWireless controllers with wired connection or XBee connection
 written by Joe St. Germain
 For RBE Class use
 joest@wpi.edu
 */
#include "Arduino.h"
#include "DFW.h"
// used in the setup portion of your program
// baud = defualt is 9600
//port_num = serial1  lowercase s defualt is serial1

void DFW::run(void) {
	update();
	unsigned long tmp = 0;
	long timeDiff = 0;
	switch (state) {
	case powerup:
		digitalWrite(robot->getDebugLEDPin(), 1);
		Serial.println("\r\nwaiting for DWF init...");
		if (!start()) {
			state = waitForAuto;
			Serial.println("\r\nwaiting for auto (press start)...");
		} else
			break;
			/* no break */
	case waitForAuto:
		if (start()) {
			robot->robotStartup();
			state = Autonomous;
			autoStartTime = millis(); // sets start time of autonomous
			Serial.println("\r\nRunning Auto...");
			// fall through when a state changes
		} else
			break;
			/* no break */

	case Autonomous:
		timeDiff = millis() - autoStartTime;
		if (timeDiff > autoTime) {
			state = waitForTeleop;
			robot->robotShutdown();
			Serial.println("\r\nwaiting for teleop (press start)...");
			// fall through when a state changes
		} else {
			tmp = millis();
			robot->autonomous(autoTime - timeDiff);
			if (functionReturnTime < (millis() - tmp)) {
				Serial.print(
						"\r\n\r\nERROR!! user Functions should return in ");
				Serial.print(functionReturnTime);
				Serial.print(" ms, took ");
				Serial.print((millis() - tmp));
				Serial.println(" ms ");
			}
			break;
		}
		/* no break */

	case waitForTeleop:
		if (start()) {
			state = Teleop;
			teleopStartTime = millis(); // sets start time of autonomous
			Serial.println("\r\nRunning Teleop...");
			// fall through when a state changes
		} else
			break;
			/* no break */
	case Teleop:
		timeDiff = millis() - teleopStartTime;
		if (timeDiff > teleopTime) {
			state = waitForAuto;
			Serial.println("\r\nwaiting for auto (press start)...");
		} else {
			tmp = millis();
			robot->teleop(teleopTime - timeDiff);
			if (functionReturnTime < (millis() - tmp)) {
				Serial.print(
						"\r\n\r\nERROR!! user Functions should return in ");
				Serial.print(functionReturnTime);
				Serial.print(" ms, took ");
				Serial.print((millis() - tmp));
				Serial.println(" ms ");
			}
			break;
		}

	}

}
void DFW::update(void) {
	while (Serial1.peek() != 'A' && Serial1.available() >= packetSize) {
		Serial1.read();
	}
	if (Serial1.peek() == 'A' && Serial1.available() >= packetSize) {
		packet[0] = Serial1.read();
		if (Serial1.peek() == 'c' && Serial1.available() >= (packetSize - 1)) {
			for (int i = 1; i < packetSize; i++) {
				packet[i] = Serial1.read();

			}
			if (packet[0] == 'A' && packet[1] == 'c' && packet[6] == 'a'
					&& packet[9] == 'B' && packet[12] == 'b') {
				for (int i = 0; i < 2; i++) {
					byteBu[i] = packet[10 + i];
				}
				for (int i = 0; i < 4; i++) {
					byteAn[i] = packet[2 + i];
				}
			}
			lastHeartBeatTime = millis();
		}
	}

	//Heartbeat need to read once every 1 seconds
	hbTime = millis() - lastHeartBeatTime;
	if (hbTime > 1000) {
		Serial.print("\r\nHB tripped clearing data. Diff= ");
		Serial.print(hbTime);
		Serial.print(" lastTime = ");
		Serial.print(lastHeartBeatTime);
		Serial.print(" current Time = ");
		Serial.print(millis());
		digitalWrite(robot->getDebugLEDPin(), 1);
		for (int i = 0; i < buttonBytes; i++) {
			byteBu[i] = 127;
		}
		for (int i = 0; i < analogBytes; i++) {
			byteAn[i] = 90;
		}
		return;

	} else {
		long timeSinceFlash = millis() - flashTime;
		if (timeSinceFlash > 1000) {
			flashTime = millis();
		} else if (timeSinceFlash > 900) {
			digitalWrite(robot->getDebugLEDPin(), 1);
		} else {
			digitalWrite(robot->getDebugLEDPin(), 0);
		}
	}
}

DFW::DFW(AbstractDFWRobot * myrobot){
	robot=myrobot;
	startup();
}
DFW::DFW(int debugpin){
	robot=new DymmyDFWRobot(debugpin);
	startup();
}
void DFW::startup(){
	state = powerup;
	pinMode(robot->getDebugLEDPin(), OUTPUT);
	digitalWrite(robot->getDebugLEDPin(), 0);
};

CompetitionState DFW::getCompetitionState(void) {
	return state;
}
void DFW::begin()    //serial1 is the only functional input
{
	Serial1.begin(9600);
	Serial1.setTimeout(250);

}

int DFW::joystickrv(void) {
	return (unsigned char) byteAn[0];
}

int DFW::joystickrh(void) {
	return (unsigned char) byteAn[1];
}

int DFW::joysticklv(void) {
	return (unsigned char) byteAn[2];
}

int DFW::joysticklh(void) {
	return (unsigned char) byteAn[3];
}

bool DFW::start(void) // returns start button state
		{
	return ((byteBu[1] & 0b00000010) == 0);
}

bool DFW::select(void) // select button state
		{
	return ((byteBu[1] & 0b00000001) == 0);
}

bool DFW::one(void) //  button one state
		{
	return ((byteBu[0] & 0b01000000) == 0);
}

bool DFW::two(void) // button two state
		{
	return ((byteBu[0] & 0b00100000) == 0);
}

bool DFW::three(void) //button three state
		{
	return ((byteBu[0] & 0b00010000) == 0);
}

bool DFW::four(void) //button four state
		{
	return ((byteBu[0] & 0b00001000) == 0);
}

bool DFW::up(void) //up button state
		{
	return ((byteBu[1] & 0b00001000) == 0);
}

bool DFW::down(void) //down button state
		{
	return ((byteBu[1] & 0b00000100) == 0);
}

bool DFW::left(void) //left button state
		{
	return ((byteBu[1] & 0b00100000) == 0);
}

bool DFW::right(void) //right button state
		{
	return ((byteBu[1] & 0b00010000) == 0);
}

bool DFW::l1(void) //L1 button state
		{
	return ((byteBu[0] & 0b00000100) == 0);
}

bool DFW::l2(void) //L2 button state
		{
	return ((byteBu[0] & 0b00000001) == 0);
}

bool DFW::r1(void) //R1 button state
		{
	return ((byteBu[0] & 0b00000010) == 0);
}

bool DFW::r2(void) //R2 button state
		{
	return ((byteBu[1] & 0b01000000) == 0);
}

void DFW::end(void) {
	Serial1.end();
}
