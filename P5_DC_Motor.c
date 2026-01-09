#include<p18f4580.h>

#define SW1 PORTDbits.RD0
#define IN1 PORTCbits.RC0
#define IN2 PORTCbits.RC1
#define EN1 PORTCbits.RC2

#define SW2 PORTDbits.RD1
#define IN3 PORTCbits.RC3
#define IN4 PORTCbits.RC4
#define EN2 PORTCbits.RC5


void delay(int count)
{
	int i, j;
	for(i = 0 ; i < count; i++)
	{
		for(j = 0; j < count; j++)
		{}
	}
}

int main()
{
	TRISC = 0x00; //Set Port C as output
	TRISDbits.RD0 = 1;
	TRISDbits.RD1 = 1;
	while(1)
	{
		if(SW1 == 0)
		{
		IN1 = 1;
		IN2 = 0;
		EN1 = 1;
		}
		else if (SW1 == 1)
		{
		EN1  = 0;
		}
	
		if(SW2 == 0)
		{
		IN3 = 1;
		IN4 = 0;
		EN2 = 1;
		}
		else if (SW2 == 1)
		{
		EN2  = 0;
		}
	}
}	