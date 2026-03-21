/*
    Timer 1 Control Register

        Bit 7          1       16 bit operation
        Bit 6          0       Clock from another source(internal)
        Bit 5-4        11      Prescaler 1:8
        Bit 3          0       Oscillator shutf off
        Bit 2          0       Ignore T1SYNC for external clock
        Bit 1          0       Internal Clock (Fosc/4)
        Bit 0          0       Stop Timer 1 intially

        T1CON = 1011 0000 = 0xb0;

    Desired Delay and TMR1H, TMR1L:

        Desired Delay = 100 ms

        F(timer) = Fosc / 4  = 1 Mhz

        F = F(timer)/Prescaler = 1M/8

        T = 1/F = 8 Us

        TMR1H, TMR1L = (2^16 - 1) - ((100*10^-3)/(8*10^-6)) = 53035 = 0xCF2B

        TMR1H = 0xCF, TMR1L = 0x2B

    Interrupt and Timer enable bits:

        T1CONbits.TMR1ON  ----      0(Stop) / 1(Start)

        PIR1bits.TMR1IF   ----      0(No overflow) / 1(Overflow)
    
*/

#include<p18f4580.h>
#define LED PORTCbits.RC0
void delay(void);

int main()
{
    int i;
    TRISCbits.RC0 = 0; //Set as output for LED
    
    T1CON = 0xb0;
    PIR1bits.TMR1IF = 0; //Reset Interrupt Flag

    while(1){
        LED = 0; //Turn off LED
        for(i = 0; i < 10; i++){
            delay();
        }

        LED = 1; //Turn ON LED
        for(i = 0; i < 10; i++){
            delay();
        }
    }
    return 0;
}

void delay(){
    TMR1H = 0xcf;
    TMR1L = 0x2b;

    T1CONbits.TMR1ON = 1;  //Enable Timer 1

    while(PIR1bits.TMR1IF != 1); //Wait for Timer 1 Interrupt to overflow

    T1CONbits.TMR1ON = 0;  //Disable Timer 1
    
    PIR1bits.TMR1IF = 0; //Reset Overflow Interrupt

}