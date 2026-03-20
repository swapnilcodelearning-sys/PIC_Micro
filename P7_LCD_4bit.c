#include<stdio.h>

#define LCD PORTC
#define EN PORTDbits.RD0
#define RW PORTDbits.RD1
#define RS PORTDbits.RD2

void delay(int count);
void LCD_init(void);
void command(char cm);
void data(char dt);
void write(const rom char* str);


int main()
{

    TRISC = 0x00; 
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    TRISDbits.RD2 = 0;

    LCD_init();

    while(1)
    {
        command(0x80); //Line 0 Position 0
        write("Next Station >");

        command(0xc0); //Line 1 Position 0
        write("Dombivli");

        command(0x01);
    }
    return 0;
}

void delay(int count){
    int i, j;
    for(i = 0; i < count; i++){
        for(j = 0; j < count; j++){}
    }
}

void LCD_init(){

    LCD = 0x0e;
    RS = 0;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;

    LCD = 0x30;
    RS = 0;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;

    LCD = 0x30;
    RS = 0;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;

    LCD = 0x30;
    RS = 0;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;

    LCD = 0x20;
    RS = 0;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;

    LCD = 0x28;
    RS = 0;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;

    command(0x01);
    command(0x06);
    command(0x80);
}

void command(char ch){
    int temp;

    temp = ch & 0xf0; //C7-C4. Higher nibble
    LCD = temp;
    RS = 0;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;

    temp = (ch & 0x0f)<<4; //C7-C4. Lower nibble pushed by 4
    LCD = temp;
    RS = 0;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;
}

void data(char dt){
    int temp;

    temp = dt & f0; //C7-C4. Higher nibble
    LCD = temp;
    RS = 1;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;

    temp = (dt & 0f)<<4; //C7-C4. Lower nibble pushed by 4
    LCD = temp;
    RS = 1;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;
}

void write(const rom char* str){
    while(*str != '\0'){
        data(*str);
        str++;
    }
}