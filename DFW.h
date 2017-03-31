/**
 * Serial controller library for DFWireless controllers
 * For RBE Class use
 * @author Joe St. Germain joest@wpi.edu
 * @author Alex Taglieri (atags22)
 * @author Kevin Harrington (madhephaestus)
 */
//written by Joe St. Germain
//
//
//
#ifndef DFW_h
#define DFW_h

#include "Arduino.h"

#define autoTime 20000
#define teleopTime  120000
#define functionReturnTime  100
enum CompetitionState {
	powerup, waitForAuto, Autonomous,waitForTeleop, Teleop
};
#define Null 0
#define buttonBytes 2
#define analogBytes 4
#define packetSize 15
class DFW {
public:
	DFW(int debugpin, void (*autonomous)( long),
			void (*teleop)( long));
	DFW(int debugpin);
	void begin();
	void run();
	int joystickrv(void);
	int joystickrh(void);
	int joysticklv(void);
	int joysticklh(void);
	bool start(void);
	bool select(void);
	bool one(void);
	bool two(void);
	bool three(void);
	bool four(void);
	bool up(void);
	bool down(void);
	bool left(void);
	bool right(void);
	bool l1(void);
	bool l2(void);
	bool r1(void);
	bool r2(void);
	bool jr(void);
	bool jl(void);
	void end(void);
	CompetitionState getCompetitionState(void);
private:
	void update(void);
	void (*myAutonomous)( long,DFW & );
	void (*myTeleop)( long,DFW & );
	long autoStartTime;
	long teleopStartTime;
	CompetitionState state;
	int packet[packetSize];
	int byteAn[analogBytes];
	int byteBu[buttonBytes];
	long lastHeartBeatTime;
	long hbTime;
	long flashTime;
	int debuginpin;
};

void autonomous( long time,DFW & dfw);
void teleop( long time,DFW & dfw);

#endif
