#include<p18f4580.h>
#define DIR_LED TRISCbits.RC0
#define LED PORTCbits.RC0
#define DIR_SW TRISCbits.RC1
#define SW PORTCbits.RC1

int main()
{
    DIR_LED = 0; //Set LED as Output
    DIR_SW = 1; //Set Switch as Input

    while(1)
    {
        if(SW == 0) //pull up
        {
            LED = 1;
        }
        else
        {
            LED = 0;
        }
    }
}