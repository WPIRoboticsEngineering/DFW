/*
 * AbstractDFWRobot.h
 *
 *  Created on: Aug 23, 2017
 *      Author: hephaestus
 */

#ifndef LIBRARIES_DFW_ABSTRACTDFWROBOT_H_
#define LIBRARIES_DFW_ABSTRACTDFWROBOT_H_
#include "DFW.h"

class AbstractDFWRobot{
public:
	/**
	 * Called when the start button is pressed and the robot control begins
	 */
	virtual void robotStartup()=0;
	/**
	 * Called by the controller between communication with the wireless controller
	 * during autonomous mode
	 * @param time the amount of time remaining
	 * @param dfw instance of the DFW controller
	 */
	virtual void autonomous( long time)=0;
	/**
	 * Called by the controller between communication with the wireless controller
	 * during teleop mode
	 * @param time the amount of time remaining
	 * @param dfw instance of the DFW controller
	 */
	virtual void teleop( long time)=0;
	/**
	 * Called at the end of control to reset the objects for the next start
	 */
	virtual void robotShutdown(void)=0;
	/**
	 * Return the number of the LED used for controller signaling
	 */
	virtual int getDebugLEDPin(void)=0;
};

class DymmyDFWRobot:public AbstractDFWRobot{
	int ledNum=13;
public:
	DymmyDFWRobot(int num){
		ledNum=num;
	}
	void robotStartup(){}
	 void autonomous( long){};
	 void teleop( long){};
	 void robotShutdown(void){};
	int getDebugLEDPin(void){
		return ledNum;
	};
};



#endif /* LIBRARIES_DFW_ABSTRACTDFWROBOT_H_ */
