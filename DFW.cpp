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

char inByteA[6];
char inByteB[3];
char byteAn[6];
char byteBu[3];
volatile long lastTime;
volatile long hbTime;
int debuginpin;


void DFW::update(void)
{
//Serial.println("updateing");
//joystick packet
  if (Serial1.find('A')) {
     // Serial.println("A");
	  for (int i = 0; i < 6; i++)
      {
        inByteA[i] = Serial1.read();
      }


    if (inByteA[5] == 'a') {
	//Serial.println("A match");
      lastTime = millis();
      byteAn[1] = inByteA[1];
      byteAn[2] = inByteA[2];
      byteAn[3] = inByteA[3];
      byteAn[4] = inByteA[4];
      byteAn[5] = inByteA[5];
	  digitalWrite(debuginpin,0);
    }
  }
  //  for (int i = 0; i < 6; i++)
 // {
   // Serial.print(byteAn[i]);
 // }

// Button Packet
  if (Serial1.find('B')) {
        for (int i = 0; i < 3; i++)
      {
        inByteB[i] = Serial1.read();
      }
    if (inByteB[2] == 'b') {
	digitalWrite(debuginpin,0);
      lastTime = millis();
      //   Serial.println("B Lock");
      for (int i = 0; i < 3; i++)  {
        byteBu[i] = inByteB[i];
      }
    }
  }

  while(Serial1.available()>0)
  {
  char clearing =Serial1.read();
  }
  
  //Heartbeat need to read once every 1 seconds
  hbTime =  millis() - lastTime;
  if (hbTime > 1000)
  {
 // Serial.println("HB tripped");
    //Serial.println("HB");
	digitalWrite(debuginpin,1);
    for (int i = 0; i < 2; i++)  {
      byteBu[i] = 127;
    }
    for (int i = 0; i < 3; i++)  {
      byteAn[i] = 90;
    }
  }

}


DFW::DFW(int debugpin)//13 is easiest
{
pinMode(debugpin,OUTPUT);
digitalWrite(debugpin,0);
debuginpin=debugpin;
}



void DFW::begin(long baud, int port)//serial1 is the only functional input
{


switch (port)
	{
	case 0:
		Serial.begin(baud);
		break;
	case 1:
		Serial1.begin(baud);
		Serial1.setTimeout(250);
		break;
	case 2:
		Serial2.begin(baud);
		break;
	case 3:
		Serial3.begin(baud);
		break;
	default:
	Serial1.begin(baud);
	break;	
}
}
 


int DFW::joystickrv(void) // returns joystick right vertical
{
//Serial.println("jrv");
unsigned char stickRv =byteAn[1];
return (stickRv);
}

int DFW::joystickrh(void) // returns joystick right vertical
{
unsigned char stickrh =byteAn[2];
return (stickrh);
}

int DFW::joysticklv(void) // returns joystick right vertical
{
unsigned char sticklv =byteAn[3];
return (sticklv);
}

int DFW::joysticklh(void) // returns joystick right vertical
{
unsigned char sticklh =byteAn[4];
return (sticklh);
}


int DFW::start(void) // returns start button state 
{
int startB;
  if(((byteBu[1] & 0b00000010) == 0b00000010))
  {
startB=1;
}
else
{
startB=0;
}
return(startB);
}


int DFW::select(void) // select button state
{
int selectB ;
if(((byteBu[1] & 0b00000001) == 0b00000001))
{
selectB=1;
}
else
{
selectB=0;
}
return(selectB);
}

int DFW::one(void)//  button one state
{
int oneB;
if(((byteBu[0] & 0b01000000) == 0b01000000))
{
oneB=1;
}
else
{
oneB=0;
}
return(oneB);
}

int DFW::two(void)// button two state
{
int twoB;
if(((byteBu[0] & 0b00100000) == 0b00100000))
{
twoB=1;
}
else
{
twoB=0;
}
return(twoB);
}

int DFW::three(void)//button three state
{
int threeB;
if(((byteBu[0] & 0b00010000) == 0b00010000))
{
threeB=1;
}
else
{
threeB=0;
}
return(threeB);
}

int DFW::four(void)//button four state
{
int fourB;
if(((byteBu[0] & 0b00001000) == 0b00001000))
{
fourB=1;
}
else
{
fourB=0;
}
return(fourB);
}

int DFW::up(void)//up button state
{
int upB;
if(((byteBu[1] & 0b00001000) == 0b00001000))
{
upB=1;
}
else
{
upB=0;
}
return(upB);
}

int DFW::down(void)//down button state
{
int downB;
if(((byteBu[1] & 0b00000100) == 0b00000100))
{
downB=1;
}
else
{
downB=0;
}
return(downB);
}

int DFW::left(void)//left button state
{
int leftB;
if(((byteBu[1] & 0b00100000) == 0b00100000))
{
leftB=1;
}
else
{
leftB=0;
}
return(leftB);
}

int DFW::right(void)//right button state
{
int rightB;
if(((byteBu[1] & 0b00010000) == 0b00010000))
{
rightB=1;
}
else
{
rightB=0;
}
return(rightB);
}

int DFW::l1(void)//L1 button state
{
int l1B;
if(((byteBu[0] & 0b00000100) == 0b00000100))
{
l1B=1;
}
else
{
l1B=0;
}
return(l1B);
}

int DFW::l2(void)//L2 button state
{
int l2B;
if(((byteBu[0] & 0b00000001) == 0b00000001))
{
l2B=1;
}
else
{
l2B=0;
}
return(l2B);
}

int DFW::r1(void)//R1 button state
{
int r1B;
if(((byteBu[0] & 0b00000010) == 0b00000010))
{
r1B=1;
}
else
{
r1B=0;
}
return(r1B);
}

int DFW::r2(void)//R2 button state
{
int r2B;
if(((byteBu[1] & 0b01000000) == 0b01000000))
{
r2B=1;
}
else
{
r2B=0;
}
return(r2B);
}
// not implemented
//int DFW::jr(void)//joystick right button state
//{
//char jrbuffer[1];
//jrbuffer[0]=inByteB[1];
//int jrB = atoi(jrbuffer);
//return(jrB);
//}
// not implemented
//int DFW::jl(void)//joystick left button state
//{
//char jlbuffer[1];
//jlbuffer[0]=inByteB[2];
//int jlB = atoi(jlbuffer);
//return(jlB);
//}


void DFW::end(void)
{
Serial1.end();
}