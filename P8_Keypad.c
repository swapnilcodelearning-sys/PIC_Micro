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
void keypad(void);

int main()
{
    TRISC = 0x00; //LCD PORTC set as output
    TRISDbits.RD0 = 0; //EN pin
    TRISDbits.RD1 = 0; //RS pin
    TRISDbits.RD2 = 0; //RW pin

    ADCON1 = 0x0f; //Set to use Port B as digital

    TRISB = 0xf0; //Keypad C4-C1 as input, Keypad R4-R1 as output

    LCD_init();

    while(1){
        keypad();
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

void keypad()
{
    PORTB = 0xfe; //R1 =0
    //C1 press check
    if(PORTB == 0xee){
        while(PORTB == 0xee);
        data('7');
    }
    //C2 press check
    if(PORTB == 0xde){
        while(PORTB == 0xde);
        data('8');
    }
    //C3 press check
    if(PORTB == 0xbe){
        while(PORTB == 0xbe);
        data('9');
    }
    //C4 press check
    if(PORTB == 0x7e){
        while(PORTB == 0x7e);
        data('/');
    }

    PORTB = 0xfd; //R2 = 0
    //C1 check
    if(PORTB == 0xed){
        while(PORTB == 0xed);
        data('6');
    }
    //C2 check
    if(PORTB == 0xdd){
        while(PORTB == 0xdd);
        data('5');
    }
    //C3 check
    if(PORTB == 0xbd){
        while(PORTB == 0xbd);
        data('4');
    }
    //C4 check
    if(PORTB == 0x7d){
        while(PORTB == 0x7d);
        data('x');
    }

    PORTB = 0xfb; //R3 =0
    if(PORTB == 0xeb){
        while(PORTB == 0xeb);
        data('3');
    }
    if(PORTB == 0xdb){
        while(PORTB == 0xdb);
        data('2');
    }
    if(PORTB == 0xbb){
        while(PORTB == 0xbb);
        data('1');
    }
    if(PORTB == 0x7b){
        while(PORTB == 0x7b);
        data('-');
    }

    PORTB = 0xf7; //R4 =0
    if(PORTB == 0xe7){
        while(PORTB == 0xe7);
        data('?');
    }
    if(PORTB == 0xd7){
        while(PORTB == 0xd7);
        data('0');
    }
    if(PORTB == 0xb7){
        while(PORTB == 0xb7);
        data('=');
    }
    if(PORTB == 0x77){
        while(PORTB == 0x77);
        data('+');
    }  
}