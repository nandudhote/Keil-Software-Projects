//#include "N76E003.h"
#include "SS_Display.h"
unsigned char temp _at_ 0x08;
unsigned char idata itemp _at_ 0x80;
unsigned char xdata xtemp _at_ 0x80;

// i2c variable start //
#define I2C_CLOCK               13
#define EEPROM_SLA             	0x09 //0x04// // ESP32 I2C Address

#define STR_SIZE 								6
#define NO_OF_DIGIT							4
UINT8 data_received[STR_SIZE];
UINT8 data_num = 0;
UINT8 ReadingStat = 0;
UINT8 i=0;

UINT8 BuzzerFlag = 0;
int BuzzerCounter = 0;
//char tempchar[]="1234";

void Init_I2C(void);

/*==========================================================================*/
void main (void) 
{
	// for uart
		//InitialUART0_Timer3(115200);
		//TI = 1;		
	///////////////
		// for GPIO CONFIGURE
		Set_All_GPIO_Quasi_Mode; 
	  /////////////													// Important, use prinft function must set TI=1;
		Init_I2C();     
		
		while(1)
		{
			//printf("\n Hello world");
			if(ReadingStat == 0){
				//printf("the value is %c,%c,%c,%c \n",data_received[0],data_received[1],data_received[2],data_received[3]);
				for(i=0; i < NO_OF_DIGIT; i++){
					SS_DigitControl((char)data_received[i], i);
					Timer0_Delay1ms(5);
				}
				if(BuzzerFlag==1){
					BuzzerCounter++;
					if(BuzzerCounter>=30){
						//BuzzerCounter=0;
						Buzzer = 1;
					}
					if(BuzzerCounter>=60){
						BuzzerFlag = 0;
						BuzzerCounter=0;
						Buzzer = 0;
					}
					
				}
				else{
					BuzzerCounter = 0;
					Buzzer = 0;
				}
				
			}
			//Timer0_Delay1ms(100);
		}//
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
    switch (I2STAT)
    {
        case 0x00:
            STO = 1;
            break;

        case 0x60:  // 
            AA = 1;
            //P3 = 0x60;
            break;
				
        case 0x68:  // Arbitration lost
						P02 = 0;
            while(1);
            break;

        case 0x80:  // Get here data
				{
					//printf("\ndata receive   ");
					if(I2DAT == 5){ // for buzzer
						BuzzerFlag = 1;
					}
					if (I2DAT == '('){
						ReadingStat = 1;
					}
					else if(ReadingStat){
						if(I2DAT != ')'){
							data_received[data_num] = I2DAT;
							//printf("  %c \n", data_received[data_num]);
							data_num++;
							if(data_num >= STR_SIZE){
								ReadingStat = 0;
								data_num = 0;
							}
						}
						else{
							//printf("\nReading stop\n");
							ReadingStat = 0;
							data_num = 0;
						}
						
					}
            //data_received[data_num] = I2DAT;
						//printf("%c",data_received[data_num]);
            //if (data_num >= STR_SIZE || data_received[data_num] == ')'){
						//	data_num = 0;
                //AA = 0;
						//}
						//data_num++;
            //else
            //    AA = 1;
				
            break;
					}
	
        case 0x88:
            //P3 = 0x88;
            //data_received[data_num] = I2DAT;
            //data_num = 0;
            AA = 1;
            break;

        case 0xA0:
            //P3 = 0xA0;
            AA = 1;
            break;

        case 0xA8:
            //P3 = 0xA0;
            //I2DAT = data_received[data_num];
            //data_num++;
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
            break; 

        case 0xC8:
            //P3 = 0xC8;
            AA = 1;
            break;    
    }

    SI = 0;
//    while(STO);
}