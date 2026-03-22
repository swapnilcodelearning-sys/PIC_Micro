#include<p18f4580.h>
#define LED PORTCbits.RC0

#pragma code InterruptVectorHigh = 0x08
    void InterruptVectorHigh(void){
        _asm goto EXT1 _endasm
    }
#pragma code

#pragma interrupt EXT1
void EXT1(void){
    TMR1H = 0x0b;
    TMR1L = 0xdb;
    LED = ~LED;
    PIR1bits.TMR1IF = 0; //Reset Interrupt Flag bit
}

int main(){
    TRISCbits.RC0 = 0; //LED as output
    
    //RCON register
    RCONbits.IPEN = 1; //Enable interrupt priority

    //INTCON register
    INTCON = 0xc0; //1100 0000 -- Global and Peripheral Interrupt

    //Timer 1 Control Register 
    T1CON = 0xb0; //1011 0000
    
    //Desired Delay TMR1H, TMR1L
    TMR1H = 0x0b;
    TMR1L = 0xdb;

    //Enable Timer 1 Interrupt 
    PIE1bits.TMR1IE = 1;

    //Enable Timer 1 Priority to high priority
    IPR1bits.TMR1IP = 1; 

    //Start Timer 1
    T1CONbits.TMR1ON = 1;

    while(1);
    return 0;
}