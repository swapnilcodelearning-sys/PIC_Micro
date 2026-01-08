#include<p18f4580.h>
#define DIR_LED TRISC 
#define LED PORTC 

void delay(int count)
{
    int i, j;
    for(i = 0; i < count; i++)
    {
        for(j = 0; j < count; j++)
        {
        }
    }
}

void pattern1()
{
    LED = 0xff; //All Pins high
    delay(100);
    LED = 0x00; //All Pins low
    delay(100);
}

void pattern2()
{
    int arr[] = {0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0x00};
    int i;
    for(i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
        LED = arr[i];
        delay(100);
    }
}

int main()
{
    DIR_LED = 0x00; //Port C set as output

    while(1)
    {
        pattern1();
        delay(100);
        pattern2();
        delay(100);
    }
}