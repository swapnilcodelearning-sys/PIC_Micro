#include<p18f4580.h>
#define LED PORTCbits.RC0

#pragma code InterruptVectorHigh=0x08
    void InterruptVectorHigh(void){
        _asm got Timer_0 _endasm
    }
#pragma code

#pragma interrupt Timer_0
void Timer_0(void){
        TMR0H = 0xfe;
        TMR0L = 0x78;
        LED = ~LED;
        INTCONbits.TMR0IF = 0; //Reset Error Flag
}

int main(){

    TRISCbits.RC0 = 0; //LED set as output
    T0CON = 0x07;  //Enable T0CON control register
    RCONbits.IPEN = 1; //Enable Interrupt Priority Level

    /*
    Bit 7       1       Enable all high priority interrupts. Global
    Bit 6       0       Disable Peripheral interrupt
    Bit 5       1       Enable TMR0 Interrupt
    Bit 4       0       INT0 Interrupt Unused
    Bit 3       0       RB Port Interrupt Unused
    Bit 2       0       TMR0 Interrupt Flag bit
    Bit 1       0       INT0 Interrupt Flag bit unused
    Bit 0       0       RB Port Interrupt Flag bit unused
    
    */
    INTCON = 0xb0; //Global Priority Enable, TMR0 Interrupt Enable
    INTCON2bits.TMR0IP = 1; //Explicitly set TMR0 Interrupt Priority to HIGH
    
    //100 ms delay
    TMR0H = 0xfe;
    TMR0L = 0x78;

    //LED
    LED = 0;

    T0CONbits.TMR0ON = 1; //Enable Timer 
    while(1);
    return 0;
}
