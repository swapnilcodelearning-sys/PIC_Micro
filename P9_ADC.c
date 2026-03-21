 #include<p18f4580.h>
 #define LCD PORTC 
 #define EN PORTDbits.RD0
 #define RW PORTDbits.RD1
 #define RS PORTDbits.RD2
 #define POT PORTAbits.RA0

 void delay(int count);
 void LCD_init(void);
 void command(char cm);
 void data(char dt);
 void write(const rom char* str);

 int main(){

    int adc_value, arr[4], i;

    TRISC = 0x00;
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    TRISDbits.RD2 = 0;

    ADCON0 = 0x01; //0 0000 01 --- AN0, GO bit Idle A/D converter enabled

    ADCON1 = 0x0e; //Setting RA0 as analog

    ADCON2 = 0x88; // 1 0 001 000 --- 1000 1000 
    TRISAbits.RA0 = 1; //Set POT as input

    LCD_init();
    while(1){
        //Set ADC Conversion bit
        ADCON0bits.GO = 1;

        while(ADCON0bits.GO == 1); //Wait for conversion completion

        adc_value = (unsigned int)(ADRESH << 8) + ADRESL;

        for(i = 0; i < 4; i++){
            arr[i] = adc_value % 10 + '0';
            adc_value = adc_value / 10;
        }
        
        command(0x80);
        write("ADC Value : ");

        command(0xc0);

        for(i = 3; i >= 0; i--){
            data(arr[i]);
            delay(5);
        }

        //command(0x01); //Clear screen 
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
    command(0x0e); //Display ON, cursor ON
    command(0x38); //5X7 Matrix
    command(0x01); //Clear screen
    command(0x06); //Increment counter
    command(0x80); //Line 0 Position 0
 }

 void command(char cm){
    LCD = cm;
    RS = 0; //Command mode
    RW = 0; //Write
    EN = 1;
    delay(50);
    EN = 0;
 }

 void data(char dt){
    LCD = dt;
    RS = 1; //Data mode
    RW = 0; //Write
    EN = 1;
    delay(50);
    EN = 0;
 }
 
 void write(const rom char* str){
    while(*str != '\0'){
        data(*str);
        str++;
    }
 }


