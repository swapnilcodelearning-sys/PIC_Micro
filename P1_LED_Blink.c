#include<p18f4580.h>
void delay(int count){
    int i, j;
    for(i = 0; i < count; i++){
        for(j = 0; j < count; j++){}
    }
}
int main(){

    TRISCbits.RC0 = 0; //Set as output
    while(1)
    {
        PORTCbits.RC0 = 1; //Set as High. LED ON
        delay(500);
        PORTCbits.RC0 = 0; //Set as Low. LED OFF
        delay(500);
    }
    return 0;
}