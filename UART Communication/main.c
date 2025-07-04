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
    char oper;   // Variable to store received character

    // Initialize UART0 using Timer1, baud rate 9600
    //InitialUART0_Timer1(9600);
	   InitialUART0_Timer3(9600);

    TI = 1;  // Enable transmit interrupt flag, required before first printf

    // Send an initial message
    //printf("Hello CircuitDigest\r\n");
	  printf("Hello CircuitDigest");
	
	
while (1)
{
    printf("\r\nPress 1 or Press 2 or Press 3 or Press 4");

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
    }
    Timer0_Delay1ms(300);
}


    /*while (1)
    {
        printf("\r\nPress 1 or Press 2 or Press 3 or Press 4");

        // Wait for user to enter a character over UART
        oper = Receive_Data_From_UART0();

        // Process the received character
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
        }
        // Small delay to avoid flooding the terminal
        Timer0_Delay1ms(300);
    }*/
		
/*		while (1)
{
    printf("\r\nPress 1 or Press 2 or Press 3 or Press 4");

    do {
        oper = Receive_Data_From_UART0();
    } while (oper == '\r' || oper == '\n');  // skip these

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
    }
    Timer0_Delay1ms(300);
}*/

}
