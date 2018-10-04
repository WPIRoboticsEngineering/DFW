#include "MyRobot.h"
#include "Arduino.h"


/**
 * Called when the start button is pressed and the robot control begins
 */
 void MyRobot::robotStartup(){
		Serial.println("Here is where I start up my robot code");
 }
/**
 * Called by the controller between communication with the wireless controller
 * during autonomous mode
 * @param time the amount of time remaining
 * @param dfw instance of the DFW controller
 */
 void MyRobot::autonomous( long time){
		Serial.print("\r\nAuto time remaining: ");
		Serial.print(time);
 }
/**
 * Called by the controller between communication with the wireless controller
 * during teleop mode
 * @param time the amount of time remaining
 * @param dfw instance of the DFW controller
 */
 void MyRobot::teleop( long time){
		Serial.print("\r\nTeleop time remaining: ");
		Serial.print(time);
		Serial.print("\tright joystick: ");
		Serial.print(dfw->joystickrv());
		Serial.print("\tleft joystick: ");
		Serial.print(dfw->joysticklv());
		//Run functions in the robot class
 }
/**
 * Called at the end of control to reset the objects for the next start
 */
 void MyRobot::robotShutdown(void){
		Serial.println("Here is where I shut down my robot code");

 }
