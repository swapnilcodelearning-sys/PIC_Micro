/*
    1. Set Interrupt Priority Level in RCON register
    2. Set INTCON to enable Global, Peripheral , Timer0/INT0 External/RB port Interrupt
    3. Set EDGE in INTCON2 register 
    4. Check Interrupt flag in ISR function, perform action and then reset interrupt flag
*/

#include<p18f4580.h>
#define LED PORTCbits.RC0

#pragma code InterruptVectorHigh=0x08
    void InterruptVectorHigh(void){
        _asm goto EXT0 _endasm
    }
#pragma code

#pragma interrupt EXT0
void EXT0(void){
    //Interrupt Flag bit checked if it occured
    if(INTCONbits.INT0IF  == 1){
        LED = ~LED;
        INTCONbits.INT0IF = 0; //Rest Interrupt Flag
    }

}


int main()
{
    TRISCbits.RC0 = 0; //LED Output
    ADCON1 = 0x0f; //Port A,B as digital
    TRISBbits.RB0 = 1; //Pull up switch at RB0/INT0

    //Enable Interrupt Priority Levels
    RCONbits.IPEN = 1;

    //Interrupt Control Register
        /*
            Bit 7       1       Enable Global Interrupt
            Bit 6       0       Disable Peripheral Interrupt
            Bit 5       0       TIMER0 Interrupt Enable bit 
            Bit 4       1       INT0 External Interrupt Enable bit
            Bit 3       0       RB port change interrupt Enable bit
            Bit 2       0       TIMER0 Interrupt Flag
            Bit 1       0       INT0 Interrupt Flag
            Bit 0       0       RB port change interrupt Flag
        */

    INTCON = 0x90;
    
    //Set Edge 
    INTCON2bits.INTEDG0 = 0; //Falling Edge
    
    while(1);
}
