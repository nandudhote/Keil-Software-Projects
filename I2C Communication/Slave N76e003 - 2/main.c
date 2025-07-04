#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
//#include "stdint.h" // for uint16_t


// i2c variable start //
#define I2C_CLOCK            13
#define EEPROM_SLA           0x15 

void Init_I2C(void);

unsigned char temp _at_ 0x08;
unsigned char idata itemp _at_ 0x80;
unsigned char xdata xtemp _at_ 0x80;

uint8_t data_received[10];
uint8_t data_num = 0;
uint16_t finalADCAVG = 1234;

volatile bit data_ready = 0;
uint8_t data_len = 0;

// define string
uint8_t data_to_send[] = "HELLO Evoluzn India";
uint8_t send_index = 0;
uint8_t send_len = sizeof(data_to_send) - 1; // minus 1 to remove null terminator


uint8_t i;

/*==========================================================================*/
void main (void) 
{
     // char oper;   // Variable to store received character

     // Initialize UART0 using Timer1, baud rate 9600
	   InitialUART0_Timer3(9600);
	
		 TI_1 = 1;
     //	Enable_ADC_AIN1;						// Enable AIN1 P3.0 as ADC input, Find in "Function_define.h" - "ADC INIT"
	
	/* Initial I2C function */
     Init_I2C();                                 //initial I2C circuit

		/*while(1)
		{
			adcval = 0;
			for(a=0; a<CTSampleSize; a++){
				clr_ADCF;
				set_ADCS;									// ADC start trig signal
				while(ADCF == 0);
				adcval = ADCRH;
				adcval = adcval << 4;
				adcval |= (ADCRL & 0x0f);
				CT[a] = adcval;
				Timer0_Delay1ms(2);
			}
			adcAvg = (adcAvg + findMax(CT, CTSampleSize));
			sampleCounter++;
			if(sampleCounter >= avgSamples){
				Timer0_Delay1ms(20);
				sampleCounter = 0;
				finalADCAVG = (uint16_t)adcAvg/avgSamples;
				adcAvg = 0;
			}	
	}*/
	
	while (1)
{
	
	if (data_ready)
    {
        printf("\nReceived string: ");

        for (i=0; i<data_len; i++)
        {
            printf("%c", data_received[i]);
        }
        printf("\n");

        data_ready = 0;   // clear flag
    }

	
	  /*if (data_ready)
    {
        printf("\ndata received: %x", data_received[data_num - 1]);
        data_ready = 0;
    }*/

    //printf("\r\nPress 1 or Press 2 or Press 3 or Press 4");

   /* while (1)
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
    Timer0_Delay1ms(300);
 }
}


void Init_I2C(void)
{
    P13_Quasi_Mode;                         //set SCL (P13) is Quasi mode
    P14_Quasi_Mode;                         //set SDA (P14) is Quasi mode
    
    SDA = 1;                                //set SDA and SCL pins high
    SCL = 1;
    
    set_P0SR_6;                             //set SCL (P06) is  Schmitt triggered input select.
    
    set_EI2C;                               //enable I2C interrupt by setting IE1 bit 0
    set_EA;

    I2ADDR = EEPROM_SLA;                    //define own slave address
    set_I2CEN;                              //enable I2C circuit
    set_AA;
}

void I2C_ISR(void) interrupt 6
{
	//printf("\n i2c interrupt happend %x", I2STAT);
    switch (I2STAT)
    {
        case 0x00:
            STO = 1;
            break;

        case 0x60:
            AA = 1;
            //P3 = 0x60;
						//printf("\ncase 0x60");
						//data_received[data_num] = I2DAT;
						//printf("\ndata receive inb 0x60 : %x", data_received[data_num]);
            break;
				
        case 0x68:
						P02 = 0;
            while(1);
            break;

        case 0x80:
            P3 = 0x80;
						//printf("\ndata received\n");
						//I2C_start();
            //I2C_write_DATA(0x25);
            //I2C_stop();
				
            //data_received[data_num] = I2DAT;
						//printf("\ndata receive in 0x80 : %x", data_received[data_num]);
				
            //data_num++;

            //if (data_num == 34)
            //    AA = 0;
            //else
            //    AA = 1;
				
				      /*data_received[data_num] = I2DAT;
				      printf("\ndata received: %x", data_received[data_num - 1]);
              data_num++;
              //data_ready = 1;
              AA = 1;*/
							
              data_received[data_num] = I2DAT;
              data_num++;
              if (data_num >= sizeof(data_received))
              {
                 data_ready = 1;   // buffer full, process in main
                 data_num = 0;     // reset index for next string
              }
              AA = 1;               // acknowledge to continue receiving	
            break;

        case 0x88:
            //P3 = 0x88;
            //data_received[data_num] = I2DAT;
            //data_num = 0;
            AA = 1;
            break;

        case 0xA0:
            //P3 = 0xA0;
				      data_len = data_num;    // store length of received string
              data_ready = 1;         // flag main loop to process
              data_num = 0;           // reset index
            AA = 1;
            break;
				
				case 0xA8:  // Master starts reading ? first byte
           /*   send_index = 0;
              I2DAT = data_to_send[send_index++];
            AA = 1; // ACK, ready to send next
            break;*/
				
				    printf("\nMaster started read, sending: %c", data_to_send[0]);
            send_index = 0;
            I2DAT = data_to_send[send_index++];
            AA = 1;
            break;

        case 0xB8:  // Master ACKed, send next byte
             /* if (send_index < send_len)
              {
              I2DAT = data_to_send[send_index++];
            AA = 1;
              }
              else
              {
            AA = 0; // no more data
              }
            break;*/
				
				  if (send_index < send_len) {
          printf("\nSending: %c", data_to_send[send_index]);
          I2DAT = data_to_send[send_index++];
          AA = 1;
          } else {
          printf("\nAll data sent");
          AA = 0;
          }
          break;

        case 0xC0:  // Master NACKed, stop
            AA = 1;
            break;
				
				
        /*case 0xA8:
						I2DAT = finalADCAVG/100; // ((finalADCAVG & 0xff00)>>8);
						clr_SI;
						while (!SI);                            //Check SI set or not
						I2DAT = finalADCAVG%100; // (finalADCAVG & 0x00ff);
            // data_num++;
            AA = 1;
            break;
        
        case 0xB8:
            //P3 = 0xB8;
            //I2DAT = data_received[data_num];
            //data_num++;
            AA = 1;
            break;

        case 0xC0:
            AA = 1;
            break;  */

        case 0xC8:
            //P3 = 0xC8;
            AA = 1;
            break;        
    }

    SI = 0;
//    while(STO);
}