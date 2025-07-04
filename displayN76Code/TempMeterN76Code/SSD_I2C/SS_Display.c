
#include "SS_Display.h"

void SS_DigitControl(char digit, ss_position position){
		
	switch(position){
		case POS_0:
			//COM &= 0x18;
			//COM |= 0x67;  // 0111 1111  // middle 0 pin is connected with i2c so should not touch
		COM0 = 0;
		COM1 = 1;
		COM2 = 1;
		COM3 = 1;
			singleSS_Control(digit);
			break;
		case POS_1:
			//COM &= 0x18;
			//COM |= 0xcf;
		COM0 = 1;
		COM1 = 0;
		COM2 = 1;
		COM3 = 1;
			singleSS_Control(digit);
			break;
		
		case POS_2:
			//COM &= 0x18;
			//COM |= 0xe6;
		COM0 = 1;
		COM1 = 1;
		COM2 = 0;
		COM3 = 1;
			singleSS_Control(digit);
			break;
		
		case POS_3:
			//COM &= 0x18;
			//COM |= 0xe5;
		COM0 = 1;
		COM1 = 1;
		COM2 = 1;
		COM3 = 0;
			singleSS_Control(digit);
			break;
		
		default:
		
			break;
		
		}
}

void singleSS_Control(char digit){
	switch (digit){
		case '-':
			DIGIT &= 0x00;
			DIGIT |= 0xbf;
			break;
		case '0':
			DIGIT &= 0x00;
			DIGIT |= 0xc0;
			break;
		case '1':
			DIGIT &= 0x00;
			DIGIT |= 0xf9;
			break;
		case '2':
			DIGIT &= 0x00;
			DIGIT |= 0xa4;
			break;
				
		case '3':
			DIGIT &= 0x00;
			DIGIT |= 0xb0;
			break;
		
		case '4':
			DIGIT &= 0x00;
			 DIGIT |= 0x99;
			break;
		
		case '5':
			DIGIT &= 0x00;
			DIGIT |= 0x92;
			break;
		
		case '6':
			DIGIT &= 0x00;
			DIGIT |= 0x82;
			break;
		case '7':
			DIGIT &= 0x00;
			DIGIT |= 0xf8;
			break;
		case '8':
			DIGIT &= 0x00;
			DIGIT |= 0x80;
			break;
		case '9':
			DIGIT &= 0x00;
			DIGIT |= 0x90;
			break;
		case 'd':
			DIGIT &= 0x00;
			DIGIT |= 0xa1;
			break;
		case 'I':
			DIGIT &= 0x00;
			DIGIT |= 0xf9;
			break;
		case 'S':
			DIGIT &= 0x00;
			DIGIT |= 0x92;
			break;
		case 'C':
			DIGIT &= 0x00;
			DIGIT |= 0xc6;
			break;
		case 'A':
			DIGIT &= 0x00;
			DIGIT |= 0x88;
			break;
		case 'L':
			DIGIT &= 0x00;
			DIGIT |= 0xc7;
			break;
		case 'E':
			DIGIT &= 0x00;
			DIGIT |= 0x86;
			break;
		case 'F':
			DIGIT &= 0x00;
			DIGIT |= 0x8e;
			break;
		case 'o':
			DIGIT &= 0x00;
			DIGIT |= 0xa3;
			break;
		case 'n':
			DIGIT &= 0x00;
			DIGIT |= 0xab;
			break;
			
	}
}