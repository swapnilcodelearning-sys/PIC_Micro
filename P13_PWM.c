/*PWM Configuration 
		PWM Frequency = 5Khz

		Fosc = 4Mhz (Internal)
		PR2 = {PWM Period / (4 * Tosc * TMR2 Pre-scaler)} - 1
			= {Fosc / (4 * PWM Frequency * TMR2 Pre-scaler)} - 1
			= { 4 * 10^6 / (4 * 5 * 10^3 * 16)} - 1
			= 12.5 - 1
			= 11.5 
			~ 11

		10% Duty Cycle = PR2 x 10% =  11 x 10/100 = 1.1

		CCPR1L =  1 (Integer before decimal point)

		-----------
		CCP1CON  = 0x0c

			Bit 7-6 	00 (Unused)

			Bit 5-4		00 (For 10% Duty Cycle)   
						DB1C1	DB1C0	Duty Cycle			
						0		0			0
						0		1			0.25
						1		0			0.5
						1		1			0.75

			Bit 3-0		1100	PWM Mode

			
			b 0000 1100 
			0x0c
		-----------


		50% Duty Cycle  =  PR2 x 50% = 5.5

		CCPR1L = 5

		CCP1CON = b 00 10 1100 = 0x2c
		
*/



#include<p18f4580.h>
#define LED PORTCbits.RC2 

void delay(int count);

int main()
{
	int i;
	//DB1C1,DB1C0 values for 0,5,10,.....100 % Duty Cycle

	int CCPR1L_arr[] = {0,0,1,1,2,2,3,3,4,4,5,6,6,7,7,8,8,9,9,10,11};
	
	// Pre-calculated CCP1CON values based on your decimal logic:
	// 0.00 -> 0x0C (00 in bits 5-4)
	// 0.25 -> 0x1C (01 in bits 5-4)
	// 0.50 -> 0x2C (10 in bits 5-4)
	// 0.75 -> 0x3C (11 in bits 5-4)

	//float CCP1CON_arr[] = { 0,0.55,0.1,0.65,0.2,0.75,0.3,0.85,0.4,0.95,0.5,0.05,0.6,0.15,0.7,0.25,0.8,0.35,0.9,0.45,0};
	int CCP1CON_arr[] = {0x0C, 0x2C, 0x0C, 0x2C, 0x0C, 0x2C, 0x0C, 0x2C, 0x0C, 0x2C, 0x2C, 0x0C, 0x2C, 0x0C, 0x2C, 0x0C, 0x2C, 0x0C, 0x2C, 0x1C, 0x0C};
	
	TRISCbits.RC2 = 0; //Output

	//No Post Scaler, Timer off, Prescaler   = 16
	T2CON =0x02; //b0 0000 0 10  
	PR2 = 11;

	T2CONbits.TMR2ON = 1; // Start Timer

	while(1)
	{
		/*
		CCP1CON = 0x0c; //10 % Duty Cycle
		CCPR1L = 1;
		delay(1000000);

		
	
		CCP1CON = 0x2c; //50 % Duty Cycle
		CCPR1L = 5;
		delay(1000000);
		*/



		for(i = 0; i < (sizeof(CCPR1L_arr)/sizeof(CCPR1L_arr[0])); i++)
		{
			CCP1CON = CCP1CON_arr[i];
			CCPR1L = CCPR1L_arr[i];
			delay(1000);
		}
	}
		
}

void delay(int count)
{
	int i, j;
	for(i = 0; i < count; i++){
	for(j = 0; j < 100; j++){}
	}
}
