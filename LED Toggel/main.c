#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

//==========================================================================
// MAIN FUNCTION
//==========================================================================
void main(void)
{
    //char oper;   // Variable to store received character

    // Initialize UART0 using Timer1, baud rate 9600
	   InitialUART0_Timer3(9600);

    TI = 1;  // Enable transmit interrupt flag, required before first printf
	
  	P12_PushPull_Mode;   // sets P1.2 to push-pull mode (output)


    // Send an initial message
    //printf("Hello CircuitDigest\r\n");
	  printf("Hello CircuitDigest");
	
	
while (1)
{
	  P12 = 1;              // LED ON
    Timer0_Delay1ms(1000); // delay 500ms

    P12 = 0;              // LED OFF
    Timer0_Delay1ms(1000); // delay 500ms

    /*printf("\r\nPress 1 or Press 2 or Press 3 or Press 4");

    while (1)
    {
        oper = Receive_Data_From_UART0();

        // skip \r and \n silently
        if (oper != '\r' && oper != '\n')
            break;
    }
				// Print what was received
        printf("\r\nYou pressed: %c", oper);
		
    switch (oper)
    {
        case '1':
            printf("\r\n1 is pressed");
            break;
        case '2':
            printf("\r\n2 is pressed");
            break;
        case '3':
            printf("\r\n3 is pressed");
            break;
        case '4':
            printf("\r\n4 is pressed");
            break;
        default:
            printf("\r\nWrong key pressed");
            break;
    }*/
    //Timer0_Delay1ms(300);
 }
}
