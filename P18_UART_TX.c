/*
    Registers :  TXSTA, RCSTA, SPBRG
    Buffers : TXREG, RXREG

    UART Data frame: 
    IDLE(1)--Start(0)--Data(5 to 9 bit)--Parity--Stop(1)--IDLE(1)

    Start always LOW, Stop always HIGH
    Parity bit 0 if even number of 1s or 1 if odd number of 1s

    1. TXSTA Transmit Status and Control Register

        Bit 7       0           ASYNC Ignore
        Bit 6       0           8 bit transmission
        Bit 5       1           Transmit Enabled
        Bit 4       0           ASYNC mode
        Bit 3       0           SENDB Sync break transmission completed
        Bit 2       1           High Speed BRGH = 1 ASYNC mode
        Bit 1       0           TSR Shift register status bit
        Bit 0       0           Address bit/Parity bit

        TXSTA = 0x24

    
    2. RCSTA Receive Status and Control Register

        Bit 7       1           Serial Port enabled
        Bit 6       0           8 bit reception
        Bit 5       0           ASYNC mode
        Bit 4       1           Enable receiver ASYNC mode

        Bit 3       0           ASYN Mode. 8 bit ignore.
        Bit 2       0           Framing Error
        Bit 1       0           Overrun Error
        Bit 0       0           Address/Parity bit. Ignore for 8 bit.
        
        RCSTA = 0x90

    3. SPBRG 

        BRGH = 1 from TXSTA bit 2

        Baud Rate = Fosc/16(N + 1)

        9600 = (4 * 10^6)/(16*(N + 1))

        N = SPBRG = 25.0416

        SPBRG = 25

    4. PIR1bits.TXIF -- UART transmit interrupt flag bit
            1 -- Empty buffer, 0 -- Buffer full

        PIR1bits.RCIF -- UART receiver interrupt flag bit
            1  --- Buffer full, 0  --- Empty buffer
        
    5. TXREG = data to write/push data when buffer is empty. Read RCREG when buffer is full
    
    6. RC6/TX = 0 (output), RC7/RX = 1 (input)
*/

#include<p18f4580.h>
void delay(void);

int main(){

    int i;
    char arr[] = "Transmitting message via UART";

    TRISCbits.RC6 = 0; //TX output
    TRISCbits.RC7 = 1; //RX input

    //UART TXSTA, RCSTA, SPBRG
    TXSTA = 0x24;
    RCSTA = 0x90;
    SPBRG = 0x19;

    //Set buffer with dummy data
    TXREG ='a';

    while(1){
        for(i = 0; arr[i] != '\0'; i++){
            while(PIR1bits.TXIF == 0); //Wait for buffer to be empty
            TXREG = arr[i]; //Fill data
        }
        delay();
    }
    return 0;
}

void delay(){
    unsigned int i, j;
    for(i = 0; i < 100; i++){
        for(j = 0; j < 100; j++){}
    }
} 