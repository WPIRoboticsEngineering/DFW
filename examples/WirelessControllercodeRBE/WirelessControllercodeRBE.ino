//This is the code running on the RBE controllers 7_6_15
//Not for student use.
//Arduino leonardo!

// # Product name: Wireless Gamepad v2.2 for Arduino
// # Product SKU : DFR0182
// # Code Version: 2.1

// # Description: Outputs 2 strings over serial. The First string is for buttons "B", ("First seven button combined into byte"),
// # ("Second seven button combined into byte"), "b" 
// # Second string is used for joysticks. ("A"), joystick right vert,joystick2 right hor,joystick left vert,joystick left hor , "a"
// # written by joseph St. Germain for WPI Robotics



int buttonState[17];
int joystick[4];
int AnalogButton[2];
boolean HB = 0;
int inputCommand = 0;
byte buttonByte1 = 0;
byte buttonByte2 = 0;
unsigned long timer = 0;

#define virbrationMotorPin 2

void setup()
{
  //  Serial.begin(9600);  //Init the Serial baudrate for testing only
  Serial1.begin(9600);  //Init the Serial1 port to enable the xbee wireless communication
  InitIO();             //Initialize the inputs/outputs and the buffers
  //  while (!Serial) {
  //  }
  while (!Serial1) {//wait for serial to init
  }
  //  Serial.print("starting controller");
}

void InitIO() {
  for (int i = 0; i < 17; i++) pinMode(i, INPUT);
  pinMode(virbrationMotorPin, OUTPUT);
  digitalWrite(virbrationMotorPin, LOW); // Stop shacking of the gamepad
}



void loop()
{
  if (millis() - timer > 25) { // manage the updating freq of all the controlling information
    // Serial.println("updating and sending");
    DataUpdate();  //read the buttons and the joysticks 
    printData();   //prints the data and states
    timer = millis();
  }

 /* if (Serial1.available()) {
    char input = Serial1.read();

    switch (input) {
      case 'v':
        Serial.println("Vibration");
        inputCommand = input;
        digitalWrite(virbrationMotorPin, HIGH);
        break;

      case 's':
        Serial.println("Stop");
        inputCommand = input;
        digitalWrite(virbrationMotorPin, LOW);
        break;
      default:
        break;
    }
  }*/
}

void DataUpdate() { //updates joysticks and buttons

  for (int i = 3; i < 17; i++)  buttonState[i] = digitalRead(i);
  buttonState[0] = analogRead(0);
  buttonState[1] = analogRead(1);
  for (int i = 2; i < 6; i++)
  {
    joystick[i - 2] = analogRead(i);
    joystick[i - 2] = map(joystick[i - 2], 0, 1024, 0, 180);

  }
  for (int i = 4; i < 6; i++)  AnalogButton[i - 4] = analogRead(i);

  buttonByte1 = 0; // prepare a serial byte based off buttons and joysticks
  buttonByte2 = 0;

  buttonByte1 |= buttonState[9] << 6 ; // Button 1
  buttonByte1 |= buttonState[11] << 5 ; // Button 2
  buttonByte1 |= buttonState[12] << 4 ; // Button 3
  buttonByte1 |= buttonState[10] << 3 ; // Button 4
  buttonByte1 |= buttonState[15] << 2 ; // Button L1
  buttonByte1 |= buttonState[13] << 1 ; // Button R1
  buttonByte1 |= buttonState[16] << 0 ; // Button L2


  buttonByte2 |= buttonState[14] << 6 ; // Button R2
  buttonByte2 |= buttonState[6] << 5 ; // Button left
  buttonByte2 |= buttonState[8] << 4 ; // Button right
  buttonByte2 |= buttonState[5] << 3 ; // Button up
  buttonByte2 |= buttonState[7] << 2 ; // Button down
  buttonByte2 |= buttonState[4] << 1 ; // Button start
  buttonByte2 |= buttonState[3] << 0 ; // Button select


}


void printData() {

//Start byte
  Serial1.print('B');//B
  Serial1.write(buttonByte1);//first 7 buttons
  Serial1.write(buttonByte2);//second 7 buttons
  Serial1.print('b'); // end byte
  Serial1.println();

  //Start byte
  Serial1.print('A');//A
  Serial1.print('c');// used to get rid of junk ???
  byte joy0 = joystick[0];
  Serial1.write(joy0);//0-180
  byte joy1 = joystick[1];
  Serial1.write(joy1);//0-180
  byte joy2 = joystick[2];
  Serial1.write(joy2);//0-180
  byte joy3 = joystick[3];
  Serial1.write(joy3);//0-180

  Serial1.print('a');// end byte
  Serial1.println();
}




