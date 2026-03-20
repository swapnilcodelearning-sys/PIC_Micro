#include<p18f4580.h>
#define PORTCbits.RC0 LED 
#define PORTCbits.RC1 SW
void delay(int count){
    int i, j;
    for(i = 0; i < count; i++){
        for(j = 0; j < count; j++){}
    }
}
int main(){

    TRISCbits.RC0 = 0; //Set LED as output
    TRISCbits.RC1 = 1; //Set Switch as input

    if(SW == 1)
    {
        LED = 1; //Turn on LED
    }
    else{
        LED = 0; //Turn off LED
    }
    return 0;
}