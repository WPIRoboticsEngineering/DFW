/* This is the RBE 1001 Template as of 7/1/15 This Template
is designed to run the autonomous and teleop sections of the final
competition. Write and test your autonomous and teleop code on your
own, then simply copy paste your code into the appropriate section
and make sure the time passed to each function corresponds with the
time in seconds that each set of code should run. IE
autonomous(20); will run for 20 seconds after the transmitter is
turned on.The code will not start until the controller is turned on, connected, and start is pressed.
There are print statements commented out that were used to test */


#include <DFW.h> // DFW include
#include <Servo.h> // servo library

int ledpindebug = 13; //Wireless controller Debug pin. If lit then there is no communication.

DFW dfw(ledpindebug);  // Instantiates the DFW object and setting the debug pin. The debug pin will be set high if no communication is seen after 2 seconds
Servo rightmotor; // Servo object
Servo leftmotor; // Servo object


void setup() {
  Serial.begin(9600); // Serial output begin. Only needed for debug
  dfw.begin(9600, 1); // Serial1 output begin for DFW library. Buad and port #."Serial1 only"
  leftmotor.attach(4, 1000, 2000); // left drive motor pin#, pulse time for 0,pulse time for 180
  rightmotor.attach(5, 1000, 2000); // right drive motor pin#, pulse time for 0,pulse time for 180
  //Serial.println("start");

  while (dfw.start() == 0) { //waits for controller to init
    Serial.println("init");
    dfw.update();
    delay(20);
  }
  // put your setup code here, to run once:

}

void autonomous(volatile unsigned long time) // function definition
{

  while (dfw.start() == 1) { // waits for start button
    Serial.println("waiting for start");
    dfw.update();
    delay(20);
  }

  unsigned long startTime = millis(); // sets start time of autonomous
  time = time * 1000; // modifies milliseconds to seconds
  while ((millis() - startTime <= time) && (dfw.select())) // compares start time to time entered in the autonomous function and
  {
    // The select button can be used to skip the autonomous code.
    // Enter Autonomous User Code Here
    Serial.println("Autonomous"); //prints Autonomous over serial (usb com port)

    dfw.update();//used for autonoumous skip
    delay(20); //delay to prevent spamming the serial port and to keep servo and dfw libraries happy

  }
}



void teleop(unsigned long time) { // function definition
  unsigned long startTime2 = millis(); // sets start time of teleop
  time = time * 1000; // modifies milliseconds to seconds
  while (millis() - startTime2 <= time) // compares start time to time entered in the teleop function
  {
    //tank drive code next 4 lines
    dfw.update();// Called to update the controllers output. Do not call faster than every 15ms.
    rightmotor.write(dfw.joystickrv());     //DFW.joystick will return 0-180 as an int into rightmotor.write
    leftmotor.write(180 - dfw.joysticklv());    //DFW.joystick will return 0-180 as an int into leftmotor.write
    delay(20); // Servos do not like to be called faster than every 20 ms. Also the Serial data is sent every 15ms

    // Enter Teleop User Code Here

    Serial.println("TeleOp"); //prints Teleop over serial (usb com port)
    delay(20); //delay to prevent spamming the serial port

  }
  exit(0); // exits program
}


void loop() {

  autonomous(20); //time in seconds to run autonomous code

  teleop(180); //time in seconds that teleop code will run
}

