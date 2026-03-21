#include<p18f4580.h>
#define LED PORTCbits.RC0

void delay(void);
int main(){

    TRISCbits.RC0 = 0;  //LED as output
    TRISCbits.RC6 = 0; // TX as output
    TRISCbits.RC7 = 1; //Rx as output

    //UART Control Register
    TXSTA = 0x24;
    RCSTA = 0x90;
    SPBRG = 0x19;

    while(1){
        while(PIR1bits.RCIF == 0); //Wait till buffer becomes full

        switch(RCREG){
            case '1':
                LED = 1; //Turn ON LED
                break;
            case '0':
                LED = 0; //Turn OFF LED
                break;
        }

        delay();
    }
    return 0;
}

void delay(){
    int i, j;
    for(i = 0; i < 100; i++){
        for(j = 0; j < 100; j++){}
    }
}