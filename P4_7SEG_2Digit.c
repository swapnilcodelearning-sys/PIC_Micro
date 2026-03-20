#include<p18f4580.h>

#define S1 PORTDbits.RD0
#define S2 PORTDbits.RD1

void delay(int count){
    int i , j;
    for(i = 0; i < count; i++){
        for(j = 0; j < count; j++){}
    }
}

int main(){

    int i, temp;
    int arr[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

    while (1)
    {
        for(i = 0; i < 100; i++){

            /*Ten's Place*/
            S1 = 0; //Enable S1
            S2 = 1; //Disable S2

            temp = i / 10;
            PORTC = arr[temp];
            delay(50);

            /*Unit's Place*/
            S2 = 0; //Enable S2
            S1 = 1; //Disable S1

            temp = i % 10;
            PORTC = arr[temp];
            delay(50);
            
        }
    }
    

    return 0;
}