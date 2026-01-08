#include<p18f4580.h>

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
    int i;

    TRISC = 0x00; //Set Port C as Output

    while(1)
    {
        for(i = 0; i < 10; i++)
        {
            PORTC = arr[i];
            delay(100);
        }
    }
}