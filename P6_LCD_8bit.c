#include<p18f4580.h>
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
    TRISC = 0x00; //LCD PORTC set as output
    TRISDbits.RD0 = 0; //EN pin
    TRISCbits.RD1 = 0; //RS pin
    TRISCbits.RD2 = 0; //RW pin

    LCD_init();

    while(1){
        command(0x80); //Line 0 Position 0
        write("Next Station >");

        command(0xc0); //Line 1 Position 0
        write("Dombivli");

        command(0x01);
    }
    return 0;
}
void delay(int count){
    int i , j;
    for(i = 0; i < count; i++){
        for(j = 0; j < count; j++){}
    }
}


void LCD_init(void){
    command(0x0e); //Display ON, Cursor ON
    command(0x38); //Load 5X7 Matrix
    command(0x01); //Clear screen
    command(0x06); //Increment counter
    command(0x80);
}

void command(char cm){
    LCD = cm;
    RS = 0;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;
}
void data(char dt){
    LCD = dt;    
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
