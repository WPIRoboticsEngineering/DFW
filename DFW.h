// Serial controller library for DFWireless controllers
//written by Joe St. Germain
//For RBE Class use
//joest@wpi.edu


#ifndef DFW_h
#define DFW_h

#include "Arduino.h"

class DFW
{
  public:
    DFW(int debugpin);
    void begin(long baud, int port_num);
	void update(void);
	int joystickrv(void);
	int joystickrh(void);
	int joysticklv(void);
	int joysticklh(void);
    int start(void);
	int select(void);
	int one(void);
	int two(void);
	int three(void);
	int four(void);
	int up(void);
	int down(void);
	int left(void);
	int right(void);
	int l1(void);
	int l2(void);
	int r1(void);
	int r2(void);
	int jr(void);
	int jl(void);
	void end(void);
  private:

};



#endif
