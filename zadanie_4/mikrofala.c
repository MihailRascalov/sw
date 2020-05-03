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

void delay(unsigned int ms) // funkcja od prowadzacego zajecia
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

void lcd_wr(unsigned char val) // funkcja od prowadzacego zajecia
{
  LPORT=val;
}

void lcd_cmd(unsigned char val) // funkcja od prowadzacego zajecia
{
	LENA=1;
        lcd_wr(val);
        LDAT=0;
        LENA=0;
	LENA=1;
}

char * obliczCzas(int sekundy) // funkcja zwraca ciag znakow, ktory posluzy do wyswietlenia
{
    char tablica[16]; // przechowuje ciag znakow do wyswietlenia
    int h = (sekundy/3600); // obliczanie godzin
    int m = (sekundy -(3600*h))/60; // obliczanie minut
    int s = (sekundy -(3600*h)-(m*60)); // obliczanie sekund
    
    sprintf(tablica, "CZAS: %d:%d       ", m, s); // zlaczanie wszystkiego razem
    return tablica; // porzadane dane
}

void lcd_dat(unsigned char val) // funkcja od prowadzacego zajecia
{
	LENA=1;
        lcd_wr(val);
        LDAT=1;
        LENA=0;
	LENA=1;
}

void opoznieniePrzycisku() // funkcja od prowadzacego zajecia
{
    unsigned int i = 6000;
    while(PORTBbits.RB1 && PORTBbits.RB2 && PORTBbits.RB3 && PORTBbits.RB4 && PORTBbits.RB5 && i > 0) // Jeżeli wscisnę to pętla zostanie przerwana
        i--;
}

void przygotujEkran() // instrukcje czesto uzywane wrzucone do funkcji
{
    lcd_cmd(L_CLR); // Czyszczenie wyswietlacza
    lcd_cmd(L_L1); // Ustawienie karetki w pierwszej linii
}

void lcd_init(void) // funkcja od prowadzacego zajecia
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

void lcd_str(const char* str) // funkcja od prowadzacego zajecia
{
    unsigned char i=0;
    while(str[i] != 0 )
    {
        lcd_dat(str[i]);
        i++;
    }  
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
    
    lcd_init(); // Inicjalizacja wyswietlacza
    lcd_cmd(L_CLR); // Czyszczenie wyswietlacza
    
    int moc;
    int stop; 
    int sekundy; 
    
    Reset: // etykieta resetu
    moc = 4; // odpowiada za wybrana wartosc Watow (domyslnie to wartosc najmniejsza)
    stop = 1; // odpowiada za stan stopu 0 urzadzenie wlaczone, 1 w stanie stop
    sekundy = 0; // zmienna uzywana do odmierzania czasu
    
    while(1)
    {
        delay(500);
        opoznieniePrzycisku(); // wcisniecie jednego z 5 przyciskow zrywa petle
        if(PORTBbits.RB5 == 0) // Jeżeli wcisnę przycisk to moc sie zmienia
        {
            moc += 1; // moc o jeden do przodu
            if(moc==5) // zabiezpiecza przed nieodpowiednimi wartosciami
                moc=1; // wartosc odpowiada 800W
        }
        
        if(moc==1 && stop==1) // wartosc odpowiada 800W
        {
            przygotujEkran(); // czyszczenie wyswietlacza i ustawienie karetki
            lcd_str("MOC: 800W       "); // uzycie wyswietlacza
        }
        
        if(moc==2 && stop==1) // wartosc odpowiada 600W
        {    
            przygotujEkran(); // czyszczenie wyswietlacza i ustawienie karetki
            lcd_str("MOC: 600W       "); // uzycie wyswietlacza
        }
        
        if(moc==3 && stop==1) // wartosc odpowiada 350W
        {
            przygotujEkran(); // czyszczenie wyswietlacza i ustawienie karetki
            lcd_str("MOC: 350W       "); // uzycie wyswietlacza
        }
        
        if(moc==4 && stop==1) // wartosc odpowiada 200W
        {
            przygotujEkran(); // czyszczenie wyswietlacza i ustawienie karetki
            lcd_str("MOC: 200W       "); // uzycie wyswietlacza
        } 
        
        if(stop==1) // wyswietlenie aktualnego czasu pozostalego do zakonczenia pracy mikrofali
        {
            lcd_cmd(L_L2); // przejscie do drugiej linii
            lcd_str(obliczCzas(sekundy)); // wywolanie funkcji przeliczajacej sekundy na minuty
        }
        
        if(PORTBbits.RB1 == 0) // RESET
        {
            przygotujEkran(); // czyszczenie wyswietlacza i ustawienie karetki
            lcd_str("RESET           "); // komunikat o resecie
            delay(500);
            goto Reset; // przekierowanie do etykiety resetu
        }
        
        if(PORTBbits.RB1 == 0) // RESET
        {
           moc = 4; // ustawienie wartosci domyslnej czyli najmniejszej mozliwej
           sekundy = 0; // wyzerowanie sekund
           lcd_cmd(L_CLR);
           lcd_cmd(L_L1);
           lcd_str("RESET           "); // komunikat o resecie
           delay(1000);
        } 

        opoznieniePrzycisku(); // wcisniecie jednego z 5 przyciskow zrywa petle
        if(PORTBbits.RB3 == 0) // dodanie czasu 10 sekund
        {
            sekundy += 10;
            lcd_cmd(L_L2); // przejscie do drugiej linii
            lcd_str(obliczCzas(sekundy)); // wyswietlenie aktualnego stanu odliczania
        }
        
        opoznieniePrzycisku(); // wcisniecie jednego z 5 przyciskow zrywa petle
        if(PORTBbits.RB4 == 0) // dodanie czasu 1 min
        {
            sekundy += 60; // 1 minuta tylko zapisywana jako sekundy
            lcd_cmd(L_L2); // przejscie do drugiej linii
            lcd_str(obliczCzas(sekundy)); // wyswietlenie aktualnego stanu odliczania
        }

        opoznieniePrzycisku(); // wcisniecie jednego z 5 przyciskow zrywa petle
        if(PORTBbits.RB2 == 0 && stop==1) // poczatek akcji (START)
        {
            if(sekundy == 0) // jezeli zapomnimy ustawic czas
            {
                przygotujEkran(); // czyszczenie wyswietlacza i ustawienie karetki
                lcd_str("USTAW CZAS      "); // komunikat o braku ustawionego czasu
            }
            else // start odliczania czasu
            {
                start:
                    opoznieniePrzycisku(); // wcisniecie jednego z 5 przyciskow zrywa petle
                    delay(500);
                    przygotujEkran(); // czyszczenie wyswietlacza i ustawienie karetki
                    lcd_str("START           "); // komunikat o starcie
                    stop = 0;
                    while(PORTBbits.RB2 != 0) // zerwanie petli podczas wcisniecia (odliczanie w dol)
                    {
                        if(PORTBbits.RB1 == 0) // RESET
                        {
                            przygotujEkran(); // czyszczenie wyswietlacza i ustawienie karetki
                            lcd_str("RESET           "); // komunikat o resecie
                            delay(500);
                            goto Reset;
                        }
                        lcd_cmd(L_L2); // przejscie do drugiej linii
                        lcd_str(obliczCzas(sekundy)); // wyswietlenie aktualnego stanu odliczania
                        if(sekundy>0) // odejmowanie sekund
                            sekundy -= 1; // po uplywie 1 sekundy -1
                        delay(500);
                        if(sekundy==0) // jezeli odliczanie dobieglo konca
                        {
                            lcd_cmd(L_L2); // przejscie do drugiej linii
                            lcd_str(obliczCzas(sekundy)); // wyswietlenie aktualnego stanu odliczania czyli 0:0
                            przygotujEkran(); // czyszczenie wyswietlacza i ustawienie karetki
                            lcd_str("GOTOWE          "); // komunikat o zakonczeniu pracy
                            break;
                        }
                    }
                    stop = 1; // proces zatrzymany
                    if (stop == 1 && sekundy>0) // proces zatrzymania
                    {
                        while(1) // nieskonczona petla
                        {
                            if(PORTBbits.RB1 == 0) // RESET
                            {
                                przygotujEkran(); // czyszczenie wyswietlacza i ustawienie karetki
                                lcd_str("RESET           "); // komunikat o resecie
                                delay(500);
                                goto Reset; // przekierowanie do etykiety resetu
                            }
                            przygotujEkran(); // czyszczenie wyswietlacza i ustawienie karetki
                            lcd_str("STOP            "); // komunikat o stopie
                            lcd_cmd(L_L2); // przejscie do drugiej linii
                            lcd_str(obliczCzas(sekundy)); // wyswietlenie aktualnego stanu odliczania
                            delay(500);
                            opoznieniePrzycisku(); // wcisniecie jednego z 5 przyciskow zrywa petle
                            if(PORTBbits.RB2 == 0) // ponowne nacisniecie start zrywa petle
                                break; // zerwanie petli
                        }
                        goto start; // przekierowanie do etykiety startowej
                    }  
            }
        }
    }
return;
}