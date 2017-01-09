
// Written bt Joseph St. Germain on 6/5/15
// This is a Tank Drive output example of the DFRobots Wireless controller. This library was written to interface through the Serial #1 port on the mega.
// The defualt design has an Xbee wireless module on either side for communication.
// The library could be altered for any serial port and may be updated to handle the other serial ports but only supports Serial1 currently.
// The DFW tank drive example needs to have 2 servo motors connected to pins 4 and 5 for driving.It also requires having a battery plugged in and turned on.

#include <DFW.h> // DFW include
#include <Servo.h> // servo library

int ledpindebug = 13; //Wireless controller Debug pin. If lit then there is no communication.

DFW dfw(ledpindebug);  // Instantiates the DFW object and setting the debug pin. The debug pin will be set high if no communication is seen after 2 seconds
Servo rightmotor; // Servo object
Servo leftmotor; // Servo object


void setup() {
  //Serial.begin(9600); // Serial output begin. Only needed for debug
  dfw.begin(9600, 1); // Serial1 output begin for DFW library. Buad and port #."Serial1 only"
  leftmotor.attach(4, 1000, 2000); // left drive motor pin#, pulse time for 0,pulse time for 180
  rightmotor.attach(5, 1000, 2000); // right drive motor pin#, pulse time for 0,pulse time for 180
  dfw.update();
    while (dfw.start() == 0) { //waits for controller to init
    Serial.println("init");
    dfw.update();
    delay(20);
  }

}

void loop() {

  dfw.update();// Called to update the controllers output. Do not call faster than every 15ms.
  rightmotor.write(180-dfw.joystickrv());     //DFW.joystick will return 0-180 as an int into rightmotor.write
  leftmotor.write(dfw.joysticklv());      //DFW.joystick will return 0-180 as an int into leftmotor.write
  delay(20); // Servos do not like to be called faster than every 20 ms. Also the Serial data is sent every 15ms 
 
}

