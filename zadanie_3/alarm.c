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

void delay(unsigned int ms) // funkcja od prowadzącego zajęcia
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

unsigned int adc(unsigned char kanal) // funkcja od prowadzącego zajęcia
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

int potentiometer() // funkcja od prowadzącego zajęcia
{
    return ((unsigned int)adc(0) / 10);
}

void main(void) 
{
    // Inicjalizacja konwertera analogowo cyfrowego
    ADCON0=0x01;
    ADCON1=0x0B;
    ADCON2=0x01;
    
    TRISA=0xC3;
    TRISB=0x3F;   
    TRISC=0x01;
    TRISD=0x00;
    TRISE=0x00;
    
    unsigned char display = 0; // wartość początkowa
    int alarmTime = 100; // przerwa pomiędzy zapaleniem, a zgaszeniem diody
    int alarmTimeSum = 0; // suma, która odpowiada za zapalenie wszystkich diod
    
    while(1) // nieskończona pętla
    {
        while(potentiometer()>51) // aktywacja alarmu po spełnieniu warunku (51 to 50% zakresu)
        {
            display = 0; // odpowiada za to, które diody palą się
            PORTD = display; // nie palą się żadne diody
            delay(alarmTime); // opóźnienie, aby dostrzegalne było mignięcie diody
            if(potentiometer()<51) // sprawdzenie czy wartość potencjometru się nie zmieniła
                break; // wyjście z pętli
            display = 1; // odpowiada za to, że 1 dioda pali się
            PORTD = display; // pali się pierwsza dioda
            delay(alarmTime); // opóźnienie, aby dostrzegalne było mignięcie diody
            if(potentiometer()<51) // sprawdzenie czy wartość potencjometru się nie zmieniła
                break; // wyjście z pętli
            alarmTimeSum = alarmTimeSum + 2 * alarmTime; // dodanie do zmiennej sumy dwóch opóźnień
            if(alarmTimeSum==1200) // po upływie 5 sekund zapalają się wszystkie diody
                while(potentiometer()>51) // sprawdzenie czy wartość potencjometru się nie zmieniła
                {
                    display = 255; // odpowiada za to, że 8 diod się pali
                    PORTD = display; // zapalenie 8 diod
                    if(PORTBbits.RB3 == 0) // warunek realizowany przy wciśnięciu przycisku RB3
                        goto Zero; // przeniesienie do miejsca, w którym zerujemy zmienne
                }
        }
        Zero: // etykieta dla zerowania zmiennych
            alarmTimeSum = 0; // wyzerowanie sumy upóźnień
            display = 0; // odpowiada za zgaszenie diod
            PORTD = display; // zgaszenie diod
    }
    return;
}