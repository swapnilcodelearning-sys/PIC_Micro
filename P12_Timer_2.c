/*
    8 Bit Timer and Period Register

    1. T2CON Control Register

        Bit7        0           Unimplemented
        Bit 6-3     0001        1:2 Postscaler
        Bit 2       0           Timer 2 On/Off
        Bit 1-0     11          1:16 Prescaler

        0000 1011

        T2CON = 0x0b

    2. Calculate PR2 for desired delay of 5 ms

        Delay = (Postscaler x PR2 x Prescaler)/(Fosc/4)

        5 * 10^-3 = (2 * PR2 * 16)/((4*10^6)/4)

        PR2 = 156.25 < 255 
            = 156(approx)

        Timer 2 counts from 0 to 156

    3. Timer 2 Enable bit and Interrupt flag

        T2CONbits.TMR2ON  -- 1(enable)/0(disable)

        PIR1bits.TMR2IF ---- 1(TMR2 to PR2 match) / 0 (No TMR2 to PR2 match )

*/

#include<p18f4580.h>
#define LED PORTCbits.RC0

void delay(void);

int main(){
    int i;
    PIR1bits.TMR2IF = 0; //Reset Timer 2 Interrupt
    TRISCbits.RC0 = 0; //Set LED as output

    T2CON = 0x0b;

    while(1){
        LED = 0;
        for(i = 0; i < 200; i++){
            delay();
        }

        LED = 1;
        for(i = 0; i < 200; i++){
            delay();
        }
    }
    return 0;
}

void delay(){
    
    PR2 = 156;

    T2CONbits.TMR2ON = 1; //Enable Timer 2

    while(PIR1bits.TMR2IF != 1); //Wait for TMR2--PR2 match 

    T2CONbits.TMR2ON = 0; //Disable Timer 2

    PIR1bits.TMR2IF = 0; //Reset Timer 2 Interrupt
}