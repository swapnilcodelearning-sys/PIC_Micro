#include<p18f4580.h>
#define IN1 PORTCbits.RC0
#define IN2 PORTCbits.RC1
#define EN1 PORTCbits.RC2

#define EN2 PORTCbits.RC3
#define IN3 PORTCbits.RC4
#define IN4 PORTCbits.RC5

void delay(int count){
    int i , j;
    for(i = 0; i < count; i++){
        for(j = 0; j < count; j++){}
    }
}

int main(){

    TRISC = 0x00; //Set PORTC as output

    while(1){

        EN1 = 1; //Enable Motor 1
        
        /*Anticlockwise*/
        IN1 = 0;
        IN2 = 1;
        delay(500);

        /*Clockwise*/
        IN1 = 1;
        IN2 = 0;
        delay(500);

        EN1 = 0; //Disable Motor 1
    }

    return 0;
}