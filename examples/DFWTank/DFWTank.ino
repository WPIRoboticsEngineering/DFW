
// Written bt Joseph St. Germain on 6/5/15
// This is a Tank Drive output example of the DFRobots Wireless controller. This library was written to interface through the Serial #1 port on the mega.
// The defualt design has an Xbee wireless module on either side for communication.
// The library could be altered for any serial port and may be updated to handle the other serial ports but only supports Serial1 currently.
// The DFW tank drive example needs to have 2 servo motors connected to pins 4 and 5 for driving.It also requires having a battery plugged in and turned on.

#include <DFW.h> // DFW include
#include <Servo.h> // servo library

class DFWRobot:public AbstractDFWRobot{
public:
	virtual void robotStartup()=0;
	virtual void autonomous( long,DFW &)=0;
	virtual void teleop( long,DFW &)=0;
	virtual void robotShutdown(void)=0;
	virtual int getDebugLEDPin(void)=0;
};

int ledpindebug = 13; //Wireless controller Debug pin. If lit then there is no communication.

DFW dfw(ledpindebug);  // Instantiates the DFW object and setting the debug pin. The debug pin will be set high if no communication is seen after 2 seconds
Servo rightmotor; // Servo object
Servo leftmotor; // Servo object

void setup() {
  Serial.begin(9600); // Serial output begin. Only needed for debug
  dfw.begin(); // Serial1 output begin for DFW library. Buad and port #."Serial1 only"
  leftmotor.attach(4, 1000, 2000); // left drive motor pin#, pulse time for 0,pulse time for 180
  rightmotor.attach(5, 1000, 2000); // right drive motor pin#, pulse time for 0,pulse time for 180
}

void loop() {
  dfw.run();// Called to update the controllers output. Do not call faster than every 15ms.
  if(dfw.getCompetitionState() != powerup){
	  rightmotor.write(180-dfw.joystickrv());     //DFW.joystick will return 0-180 as an int into rightmotor.write
	  leftmotor.write(dfw.joysticklv());      //DFW.joystick will return 0-180 as an int into leftmotor.write
  }
}

