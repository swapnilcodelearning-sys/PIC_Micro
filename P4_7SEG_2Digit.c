#include<p18f4580.h>
#define S1 PORTDbits.RD0
#define S2 PORTDbits.RD1

void delay(int count)
{
    int i, j;
    for(i = 0 ; i < count; i++)
    {
        for(j = 0; j < count; j++){}
    }
}

int main()
{
    //Need to declare variable before for MPLAB IDE
    int arr[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; //0-9 Common Cathode array
    int i,temp;

    TRISC = 0x00; //Set Port C as Output
    
    //TRISD = 0x00; //Set Port D as Output
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;

    while(1)
    {
        for(i = 0 ; i < 100; i++)
        {
            //Ten's Place
            S1 = 0;
            S2 = 1;
            temp = i/10;
            PORTC = arr[temp];
            delay(50);

            //Units Place 
            S1 = 1;
            S2 = 0;
            temp = i%10;
            PORTC = arr[temp];
            delay(50);

        }
    }
}