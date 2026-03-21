#include<p18f4580.h>
#define LED PORTCbits.RC0

#pragma code InterruptVectorHigh=0x08
    void InterruptVectorHigh(void){
        _asm goto EXT1 _endasm
    }
#pragma code

#pragma interrupt EXT1
void EXT1(void){
    //Check if INT1 interrupt flag is set
    if(INTCON3bits.INT1IF == 1){
        LED = ~LED;
        INTCON3bits.INT1IF = 0; //Reset INT1 interrupt flag bit
    }   
}

int main()
{
    TRISCbits.RC0 = 0; //LED Output
    TRISBbits.RB1 = 1; //Switch at RB1/INT1

    //Enable Interrupt Priority Level
    RCONbits.IPEN = 1;

    //Enable INTCON
    INTCON = 0x80; // 1000 0000 -- Only enable Global interrupt

    //Enable External Interrupt 1 
    /*
        Bit 7       0       INT2 External Interrupt Priority Bit(Unused)
        Bit 6       1       Set INT1 Interrupt Priority bit
        Bit 5       0       Unused
        Bit 4       0       INT2 Enable bit. Unused
        Bit 3       1       INT1 Enable bit
        Bit 2       0       Unused
        Bit 1       0       INT2 interrupt flag bit
        Bit 0       0       INT1 interrupt flag bit
    
        0100 1000 
    */
    INTCON3 = 0x48; 

    //Set Edge
    INTCON2bits.INTEDG1 = 0; //Falling Edge

    while(1);
    return 0;
}