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
bool provisionTerminal = false;
byte written=0;

#define virbrationMotorPin 2

void setup() {
	Serial1.begin(9600); //Init the Serial1 port to enable the xbee wireless communication
	InitIO();             //Initialize the inputs/outputs and the buffers
	while (!Serial1) {             //wait for serial to init
	}
  DataUpdate();  //read the buttons and the joysticks
  if(!buttonState[4]){// sheckStart button on boot
        provisionTerminal = true;
        
  }
  if(provisionTerminal){// sheckStart button on boot
        Serial.begin(9600); // Serial output begin. Only needed for debug
        Serial.println("Starting with provision terminal");
  }
}

void InitIO() {
	for (int i = 0; i < 17; i++)
		pinMode(i, INPUT);
	pinMode(virbrationMotorPin, OUTPUT);
	digitalWrite(virbrationMotorPin, LOW); // Stop shacking of the gamepad
}

void dump(){
  int start = millis();
  
  while(Serial1.available()<=0){
    if((millis()-start)>5000){
      Serial.print("\r\nNO RESPONSE\r\n");
      return;
    }
    //delay(1);
  }
  while(Serial1.available()>0){
      byte val=Serial1.read();
      if(val>8 && val< 127){
        written++;
        Serial.write(val);
      }
      //delay(1);
  }
}

void write (String s){
  //written=0;
  Serial.print("\r\n");
  Serial.print(s);
  Serial.print("\r\n");
  Serial1.print(s);
}


void initializeContolMode(){
          /*
       * This section is a secret code: 
       * ~ 0x0  0x4  0x8  0x1 A  P  e
       * sent by XCTU to kick the module into AT mode
       * This needs to be sent before initating AT mode
       */
      Serial1.write('~');
      Serial1.write(0x4);
      Serial1.write(0x8);
      Serial1.write(0x1);
      Serial1.write('A');
      Serial1.write('P');
      Serial1.write('e');
      start();
      write("ATAP\r");
      dump();
      write("ATHV\r");
      dump();
      write("ATVR\r");
      dump();
      write("ATSH\r");
      dump();
      write("ATSL\r");
      dump();
      write("ATMY\r");
      dump();
      write("ATAC\r");
      dump();
      write("ATBD\r");
      dump();
      write("ATNB\r");
      dump();
      write("ATSB\r");
      dump();
      write("ATAP\r");
      dump();
      write("ATCN\r");
      dump();
}


void start(){

      delay(1500);
      Serial1.write("+++");
      Serial.write("+++");
      delay(1000);
      dump();
}

void end(){
      write("ATWR\r");
      dump();
      write("ATAC\r");
      dump();
      write("ATCN\r");
      dump();
}

void provisionTerminalRun(){

  if(Serial.available()>1){
    String number = Serial.readString();
      Serial.write("\r\nProvisioning...");
      Serial.print(number);
      initializeContolMode();
     
      start();
      write("ATIDB");
      write(number);
      write("\r");
      dump();
      end();
      
      start();
      write("ATCE0\r");
      dump();
      end();

      //Close up connection

      if(written>1){
        Serial.write("\r\nDone!");
      }else{
          Serial.write("\r\nFailed!! module dead..");
        
      }
    provisionTerminal=false;
  }
}

void loop() {
	if (millis() - timer > 25) { // manage the updating freq of all the controlling information
		// Serial.println("updating and sending");
		DataUpdate();  //read the buttons and the joysticks
		if(!provisionTerminal)
		  printData();   //prints the data and states
		timer = millis();
	}
 if(provisionTerminal){
  provisionTerminalRun();
 }

}

void DataUpdate() { //updates joysticks and buttons

	for (int i = 3; i < 17; i++)
		buttonState[i] = digitalRead(i);
	buttonState[0] = analogRead(0);
	buttonState[1] = analogRead(1);
	for (int i = 2; i < 6; i++) {
		joystick[i - 2] = analogRead(i);
		joystick[i - 2] = map(joystick[i - 2], 0, 1024, 0, 180);

	}
	for (int i = 4; i < 6; i++)
		AnalogButton[i - 4] = analogRead(i);

	buttonByte1 = 0; // prepare a serial byte based off buttons and joysticks
	buttonByte2 = 0;

	buttonByte1 |= buttonState[9] << 6; // Button 1
	buttonByte1 |= buttonState[11] << 5; // Button 2
	buttonByte1 |= buttonState[12] << 4; // Button 3
	buttonByte1 |= buttonState[10] << 3; // Button 4
	buttonByte1 |= buttonState[15] << 2; // Button L1
	buttonByte1 |= buttonState[13] << 1; // Button R1
	buttonByte1 |= buttonState[16] << 0; // Button L2

	buttonByte2 |= buttonState[14] << 6; // Button R2
	buttonByte2 |= buttonState[6] << 5; // Button left
	buttonByte2 |= buttonState[8] << 4; // Button right
	buttonByte2 |= buttonState[5] << 3; // Button up
	buttonByte2 |= buttonState[7] << 2; // Button down
	buttonByte2 |= buttonState[4] << 1; // Button start
	buttonByte2 |= buttonState[3] << 0; // Button select
}

void printData() {
//Start byte
	Serial1.print('B'); //B 0
	Serial1.write(buttonByte1); //first 7 buttons 1
	Serial1.write(buttonByte2); //second 7 buttons 2
	Serial1.print('b'); // end byte 3
	Serial1.println(); // 4 5

	//Start byte
	Serial1.print('A'); //A 6
	Serial1.print('c'); // used to get rid of junk ??? 7
	byte joy0 = joystick[0]; //
	Serial1.write(joy0); //0-180 8
	byte joy1 = joystick[1];
	Serial1.write(joy1); //0-180 9
	byte joy2 = joystick[2];
	Serial1.write(joy2); //0-180 10
	byte joy3 = joystick[3];
	Serial1.write(joy3); //0-180 11
	Serial1.print('a'); // end byte 12
	Serial1.println(); // 13
}
