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
    uint16_t adcval = 0;

    // Initialize UART0 using Timer3, baud rate 9600
    InitialUART0_Timer3(9600);
    TI = 1;  // Enable transmit interrupt flag before first printf

    Enable_ADC_AIN1;  // Enable ADC on pin P1.6 (AIN1)

    while (1)
    {
			  char adcString[16];
			
        // Start ADC conversion
        clr_ADCF;    // Clear ADC finish flag
        set_ADCS;    // Start ADC
        while (ADCF == 0);  // Wait until finish

			  // Read ADC value For 12 bit
			  //adcval = ADCRH;
				//adcval = adcval << 4;
				//adcval |= (ADCRL & 0x0f);
			
        // Read ADC value (10-bit right-aligned)
        adcval = ((ADCRH << 8) | ADCRL) & 0x03FF;  // Mask to keep only 10 bits

        // Print the ADC value
        printf("ADC Value: %u\r\n", adcval);
			
			 
        sprintf(adcString, "%u", adcval);

        // Now you can print it:
        printf("ADC String: %s\r\n", adcString);


        Timer0_Delay1ms(1000);  // Delay 1 second
    }
}
