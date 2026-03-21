/*
    1. Timer 0  Control Register

        Bit 7   0       Timer off
        Bit 6   0       16 Bit
        Bit 5   0       Internal Microcontroller clock
        Bit 4   0       Edge Selection Low to High

        Bit 3   0       Prescaler assigned
        Bit 2-0 111     Prescaler 1:256
    
        T0CON = 0x07 

    2. Delay and TMR0H, TMR0L
        
        F(timer) = Fosc/4 = 1 Mhz

        F = F(timer)/Pre-scaler = 1 M/256

        T = 1/F = 256 Us

        Desired Delay = 100 ms

        TMR0H, TMR0L = (2^16 -1) - (Desired Delay/T)
                    = 65535 - (100m/256U)
                    = 65144
                    = 0xfe78

    3. Interrupt Flag

        INTCONbits.TMR0IF ---  0 (Reset), 1(Set)

    4. Timer 0 ON/OFF bits

        T0CONbits.TMR0ON --- 1 (Enable)/ 0 (Disable)
*/

#include<p18f4580.h>
#define LED PORTCbits.RC0

void delay(void);

int main(){

    int i;
    TRISCbits.RC0 = 0; //LED set as output
    T0CON = 0x07;  //Enable T0CON control register
    
    while(1){
        LED = 0;
        for(i = 0; i < 10; i++){
            delay();
        }

        LED = 1;
        for(i = 0; i < 10; i++){
            delay();
        }
    }
    return 0;
}


void delay()
{
    TMR0H = 0xfe;
    TMR0L = 0x78;

    T0CONbits.TMR0ON = 1; //Enable Timer 0

    while(INTCONbits.TMR0IF != 1); //Wait for Timer 0 to overflow from 65144 to 65535(0xffff)

    T0CONbits.TMR0ON = 0; //Disbale Timer 0

    INTCONbits.TMR0IF = 0; //Rest Interrupt flag
}