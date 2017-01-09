// Written bt Joseph St. Germain on 6/5/15
// This is a Serial output example of the DFRobots Wireless controller. This library was written to interface through the Serial #1 port on the mega.
// The defualt design has an Xbee wireless module on either side for communication.
// The library could be altered for any serial port and may be updated to handle the other serial ports.
// The DFW l

#include <DFW.h> // DFW include

int ledpindebug = 13;
DFW dfw(ledpindebug);  // Instantiates the DFW object and setting the debug pin. The debug pin will be set high if no communication is seen after 2 seconds
void setup() {
  Serial.begin(9600); // Serial output begin
  dfw.begin(9600, 1); // Serial1 output begin for DFW library. Buad and port #."Serial1 only"
}

void loop() {
  dfw.update();// Called to update the controllers output
  if (dfw.start() == 0 ) {   //DFW.button() will return button state.Buttons defualt to 1. value switches to 0 when pressed
    Serial.println("start");
  }
  if (dfw.select() == 0 ) {
    Serial.println("select");
  }

  if (dfw.up() == 0 ) {
    Serial.println("up");
  }
  if (dfw.down() == 0 ) {
    Serial.println("down");
  }
  if (dfw.left() == 0 ) {
    Serial.println("left");
  }
  if (dfw.right() == 0 ) {
    Serial.println("right");
  }

  if (dfw.r1() == 0 ) {
    Serial.println("r1");
  }
  if (dfw.r2() == 0 ) {
    Serial.println("r2");
  }
  if (dfw.l1() == 0 ) {
    Serial.println("l1");
  }
  if (dfw.l2() == 0 ) {
    Serial.println("l2");
  }
  if (dfw.one() == 0 ) {
    Serial.println("one");
  }
  if (dfw.two() == 0 ) {
    Serial.println("two");
  }
  if (dfw.three() == 0 ) {
    Serial.println("three");
  }
  if (dfw.four() == 0 ) {
    Serial.println("four");
  }

  if (dfw.joystickrh() > 92 | dfw.joystickrh() < 87) {  // prevents continous output.
    Serial.print("joyrh:");
    Serial.println(dfw.joystickrh());                 //DFW.joystick will return 0-180 as an int.
  }

  if (dfw.joystickrv() > 92 | dfw.joystickrv() < 87) {
    Serial.print("joyrv:");
    Serial.println(dfw.joystickrv());
  }

  if (dfw.joysticklh() > 92 | dfw.joysticklh() < 87) {
    Serial.print("joylh:");
    Serial.println(dfw.joysticklh());
  }
  if (dfw.joysticklv() > 92 | dfw.joysticklv() < 87) {
    Serial.print("joylv:");
    Serial.println(dfw.joysticklv());
  }
  // put your main code here, to run repeatedly:

  delay(25);

}

