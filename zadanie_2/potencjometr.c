// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF

#include <xc.h>

void delay(unsigned int ms) // funkcja od prowadz?cego zaj?cia
{
    unsigned int i;
    unsigned char j;
    
    for (i =0; i< ms; i++)
    {
        for (j =0 ; j < 200; j++)
        {
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
        }
    }
}

unsigned int adc(unsigned char kanal) // funkcja od prowadz?cego zaj?cia
{
    switch(kanal)
    {
        case 0: ADCON0=0x01; break; //P1
        case 1: ADCON0=0x05; break; //P2
        case 2: ADCON0=0x09; break; 
    }
    ADCON0bits.GO=1;
    while(ADCON0bits.GO == 1);

   return ((((unsigned int)ADRESH)<<2)|(ADRESL>>6));
}

unsigned char IntToGray(unsigned char input) // funkcja od prowadz?cego zaj?cia
{
    return input ^ (input >> 1);
}

void keysSlow() // funkcja od prowadz?cego zaj?cia
{
    unsigned int i = 6000; // Spowolnienie przycisków
    while(PORTBbits.RB4 && PORTBbits.RB3 && i > 0)
        i--;
}

int potentiometer() // funkcja od prowadz?cego zaj?cia
{
    return ((unsigned int)adc(1) / 10);
}

int delayFrompotentiometer(int x) // funkcja s?u?y od generowania opó?nienia w zale?no?ci
// od stanu potencjometru (warto?ci, które obs?ugujemy 0-102)
{
    if(x >= 0 && x <=20) // maksymalne spowolnienie 100%
        return 650; // d?ugo?? opó?nienia
    if(x >= 21 && x <=40) // spowolnienie 80%
        return 500; // d?ugo?? opó?nienia
    if(x >= 41 && x <=61) // spowolnienie 60%
        return 350; // d?ugo?? opó?nienia
    if(x >= 62 && x <=81) // spowolnienie 40%
        return 200; // d?ugo?? opó?nienia
    if(x >= 82 && x <=102) // spowolnienie 20%
        return 50; // d?ugo?? opó?nienia
    else // warto?? ustalana w przypadku nieprzewidzianych sytuacji
        return 500; // d?ugo?? opó?nienia
}

void main(void) 
{
    //Inicjalizacja konwertera analogowo cyfrowego
    ADCON0=0x01;
    ADCON1=0x0B;
    ADCON2=0x01;
    
    TRISA=0xC3;
    TRISB=0x3F;   
    TRISC=0x01;
    TRISD=0x00;
    TRISE=0x00;
    
    unsigned char display = 7; // s?u?y do wy?wietlenia w??yka
    unsigned char gray = 0; // s?u?y do wy?wietlenia stanu licznika graya
    
    while(1) // niesko?czona p?tla
    {        
        keysSlow(); // drobne spowolnienie odczytu przycisków
        ThreeBitSnake_7: // etykieta
            display = 7; // warto?? pocz?tkowa
            for(int i=0; i<6; i++) // p?tla odpowiedzialna za ruch w dó? w??yka
            {
                keysSlow(); // drobne spowolnienie odczytu przycisków
                if(PORTBbits.RB3 == 1 && PORTBbits.RB4 == 1) // warunek wykonywany podczas braku wci?ni?cia
                {
                    PORTD = display << i; // wy?wietlenie obecnego stanu w??yka (kierunek dó?)
                    delay(delayFrompotentiometer(potentiometer())); // opó?nienie sterowane przez potencjometr
                }
                else // wykonanie podczas wcisni?cia
                    goto binaryGrayCounterUp_4; // przej?cie do wykonywania innego podprogramu
            }
            display = 224; // warto?c kra?cowa
            for(int j=1; j<5; j++) // p?tla odpowiedzialna za ruch w gór? w??yka
            {
                keysSlow(); // drobne spowolnienie odczytu przycisków
                if(PORTBbits.RB3 == 1 && PORTBbits.RB4 == 1) // warunek wykonywany podczas braku wci?ni?cia
                {
                    PORTD = display >> j; // wy?wietlenie obecnego stanu w??yka (kierunek góra)
                    delay(delayFrompotentiometer(potentiometer())); // opó?nienie sterowane przez potencjometr
                }
                else // wykonanie podczas wcisni?cia
                    goto binaryGrayCounterUp_4; // przej?cie do wykonywania innego podprogramu
            }
            display = 7; // ustawienie warto?ci pocz?tkowej
            goto ThreeBitSnake_7; // przej?cie na pocz?tek podprogramu
        
        binaryGrayCounterUp_4: // etykieta
            keysSlow(); // drobne spowolnienie odczytu przycisków
            if(PORTBbits.RB3 == 1 && PORTBbits.RB4 == 1) // warunek wykonywany podczas braku wci?ni?cia
            {
                PORTD = IntToGray(gray); // wy?wietlenie obecnego stanu kodu graya
                delay(delayFrompotentiometer(potentiometer())); // opó?nienie sterowane przez potencjometr
                gray++; // zwi?kszenie stanu licznika o 1
                goto binaryGrayCounterUp_4; // przej?cie na pocz?tek podprogramu
            }
            else // wykonanie podczas wcisni?cia
            {
                gray = 0; // zerowanie licznika kodu graya
                goto ThreeBitSnake_7; // przej?cie do wykonywania innego podprogramu
            }          
    }
    return;
}