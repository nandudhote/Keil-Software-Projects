
#include "N76E003.h"

#ifndef SS_DISPLAY
#define SS_DISPLAY

#define Buzzer P12

#define COM0 P17
#define COM1 P15
#define COM2 P10
#define COM3 P11

#define COM	 P1

#define F P06
#define G P05
#define E P04
#define D P03
#define DP P07
#define C P02
#define B P01
#define A P00

#define DIGIT P0
typedef enum ss_position{
		POS_0,
		POS_1,
		POS_2,
		POS_3
}ss_position;

void SS_DigitControl(char digit, ss_position position);
void singleSS_Control(char digit);


#endif