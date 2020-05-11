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
#include<stdio.h>

#define LENA  PORTEbits.RE1
#define LDAT  PORTEbits.RE2
#define LPORT PORTD

#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0
#define L_CR	0x0F		
#define L_NCR	0x0C	

#define L_CFG   0x38

void delay(unsigned int ms)
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

unsigned int adc(unsigned char kanal)
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

void lcd_wr(unsigned char val)
{
    LPORT=val;
}

void lcd_cmd(unsigned char val)
{
    LENA=1;
        lcd_wr(val);
        LDAT=0;
        LENA=0;
	LENA=1;
}
 
void lcd_dat(unsigned char val)
{
	LENA=1;
        lcd_wr(val);
        LDAT=1;
        LENA=0;
	LENA=1;
}

void lcd_init(void)
{
	LENA=0;
	LDAT=0;
	delay(20);
	LENA=1;
	
	lcd_cmd(L_CFG);
	delay(5);
	lcd_cmd(L_CFG);
        delay(1);
	lcd_cmd(L_CFG); //configura
	lcd_cmd(L_OFF);
	lcd_cmd(L_ON); //liga
	lcd_cmd(L_CLR); //limpa
	lcd_cmd(L_CFG); //configura
        lcd_cmd(L_L1);
}

void lcd_str(const char* str)
{
    unsigned char i=0;
    while(str[i] != 0 )
    {
        lcd_dat(str[i]);
        i++;
    }  
}

int potentiometer() // funkcja od prowadzącego zajęcia
{
    return ((unsigned int)adc(1) / 10);
}

int timeFromPotentiometer(int x) // funkcja służy do generowania czasu w zależności od ustawienia potencjometru (wartości, które obsługujemy 0-102)
{
    if(x >= 0 && x <=34) // Ustawiamy czas na 1 min
        return 60; // zwracany czas
    if(x >= 35 && x <=68) // Ustawiamy czas na 3 min
        return 60*3; // zwracany czas
    if(x >= 69 && x <=102) // Ustawiamy czas na 5 min
        return 60*5; // zwracany czas
    else // wartość ustalana w przypadku nieprzewidzianych sytuacji
        return 1; // zwracany czas
}

char * obliczCzas(int sekundy, int sekundy2) // funkcja zwraca ciag znakow, ktory posluzy do wyswietlenia
{
    char tablica[16]; // przechowuje ciag znakow do wyswietlenia
    int h = (sekundy/3600); // obliczanie godzin
    int m = (sekundy -(3600*h))/60; // obliczanie minut
    int s = (sekundy -(3600*h)-(m*60)); // obliczanie sekund
    
    int h2 = (sekundy2/3600); // obliczanie godzin
    int m2 = (sekundy2 -(3600*h2))/60; // obliczanie minut
    int s2 = (sekundy2 -(3600*h2)-(m2*60)); // obliczanie sekund
    
    if(s>=10 && s2>=10) // jeżeli zmienne s oraz s2 przechowujace sekundy mają dwa znaki np. 10, 18
        sprintf(tablica, "0%d:%d      0%d:%d", m, s, m2, s2); // zlaczanie wszystkiego razem
    else if(s>=10 && s2<10) // jeżeli zmienne s oraz s2 przechowujace sekundy mają dwa znaki np. 10 oraz jeden znak np. 5
        sprintf(tablica, "0%d:%d      0%d:0%d", m, s, m2, s2); // zlaczanie wszystkiego razem
    else if(s<10 && s2>=10) // jeżeli zmienne s oraz s2 przechowujace sekundy mają jeden znak np. 3 oraz dwa znaki np. 45
        sprintf(tablica, "0%d:0%d      0%d:%d", m, s, m2, s2); // zlaczanie wszystkiego razem
    else // jeżeli zmienne s oraz s2 przechowujace sekundy mają po jednym znaku np. 6, 8
        sprintf(tablica, "0%d:0%d      0%d:0%d", m, s, m2, s2); // zlaczanie wszystkiego razem
    return tablica; // porzadane dane
}

void opoznieniePrzycisku() // funkcja od prowadzacego zajecia
{
    unsigned int i = 6000;
    while(PORTBbits.RB3 && PORTBbits.RB5 && i > 0) // Jeżeli wcisnę to pętla zostanie przerwana
        i--;
}

void przygotujEkran() // instrukcje czesto uzywane wrzucone do funkcji
{
    lcd_cmd(L_CLR); // Czyszczenie wyswietlacza
    lcd_cmd(L_L1); // Ustawienie karetki w pierwszej linii
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
    
    lcd_init(); //Inicjalizacja wyświetlacza
    lcd_cmd(L_CLR); //Czyszczenie wyświetlacza
    
    int sekundy = 0; // zmienna uzywana do odmierzania czasu
    int czasPierwszegoGracza; // zmienna uzywana do przechowywania czasu pierwszego gracza
    int czasDrugiegoGracza; // zmienna uzywana do przechowywania czasu drugiego gracza
    
    Start: // etykieta wskazująca początek programu
        while(1)
        {
            delay(500); // opóźnienie
            sekundy = timeFromPotentiometer(potentiometer()); // pobranie wartości sekund z potencjometru (60, 180 lub 300 sekund)
            czasPierwszegoGracza = sekundy; // przypisanie pierwszemu graczowi pobranych sekund
            czasDrugiegoGracza = sekundy; // przypisanie drugiemu graczowi pobranych sekund
            przygotujEkran(); // przygotowanie ekranu
            lcd_str(obliczCzas(sekundy, sekundy)); // wyswietlenie aktualnego stanu odliczania
            lcd_cmd(L_L2); // przejscie do drugiej linii
            lcd_str("STOP        STOP"); // stan początkowy
            while(PORTBbits.RB3 == 0) // inicjalizacja gry przez pierwszego gracza
                goto DrugiGracz; // przejście do drugiego gracza
        }
    
    DrugiGracz: // etykieta wskazująca drugiego gracza
        while(1)
        {
            while(PORTBbits.RB5 != 0) // jeżeli wciśniemy zrywamy pętlę
            {
                przygotujEkran(); // przygotowanie ekranu
                lcd_str(obliczCzas(czasPierwszegoGracza, czasDrugiegoGracza)); // wyswietlenie aktualnego stanu odliczania
                lcd_cmd(L_L2); // przejscie do drugiej linii
                lcd_str("STOP        MOVE"); // stan oczekiwania na wykonanie ruchu
                if(czasDrugiegoGracza>0) // odejmowanie sekund
                    czasDrugiegoGracza -= 1; // po uplywie 1 sekundy -1
                else
                    goto Komunikat; // wyświetlenie komunikatu o przegranej
                delay(500); // opóźnienie
            }
            goto PierwszyGracz; // przejście do pierwszego gracza
        }
    
    PierwszyGracz: // etykieta wskazująca pierwszego gracza
        while(1)
        {
            while(PORTBbits.RB3 != 0) // pierwszy gracz
            {
                przygotujEkran(); // przygotowanie ekranu
                lcd_str(obliczCzas(czasPierwszegoGracza, czasDrugiegoGracza)); // wyswietlenie aktualnego stanu odliczania
                lcd_cmd(L_L2); // przejscie do drugiej linii
                lcd_str("MOVE        STOP"); // stan oczekiwania na wykonanie ruchu
                if(czasPierwszegoGracza>0) // odejmowanie sekund
                    czasPierwszegoGracza -= 1; // po uplywie 1 sekundy -1
                else
                    goto Komunikat; // wyświetlenie komunikatu o przegranej
                delay(500); // opóźnienie
            }
            goto DrugiGracz; // przejście do drugiego gracza
        }
    
    Komunikat: // etykieta komunikatu
        lcd_cmd(L_L2); // przejscie do drugiej linii
        lcd_str("TIME OUT = LOST "); // komunikat oświadczający przegraną
        delay(1000); // opóźnienie
        goto Start; // przejście do początku programu
    return;
}