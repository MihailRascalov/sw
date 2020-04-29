#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void IntToBinary(unsigned char input) // funkcja od prowadzącego
{
    short i = 7;
    while(i>=0)
    {
        printf("%d",(input >> i) & 1);
        i--;
    }
    printf("   ");
}

void Slow() // funkcja od prowadzącego delikatnie zmodyfikowana
{
    int c,d = 0;
    for (c = 1; c <= 32767; c++)
        for (d = 1; d <= 16384; d++) // modyfikacja z 8192‬ na 16384
        {}
}

unsigned char IntToGray(unsigned char input) // funkcja od prowadzącego
{
    return input ^ (input >> 1);
}

unsigned char IntToBCD(unsigned char input) // funkcja od prowadzącego
{
    return ((input / 10) << 4) | (input % 10);
}

int main(void)
{
unsigned char display=0; // zmienna używana do wyświetlania wyniku
unsigned char counter = 0; // zmienna używana w liczniku binarnym i graya
unsigned char counterBCD = 0; // zmienna używana w liczniku BCD

binaryCounterUp_1: // 8 bitowy licznik binarny zliczający w górę (0…255)
    while( !_kbhit() ) // wciśnięcie przycisku kończy działanie pętli
    {
        printf("\r                                                                          ");
        printf("\r[1] 8 bitowy licznik binarny zliczajacy w gore: ");
        IntToBinary(display); // wywołanie funkcji zmieniającej system dziesiętny na system dwójkowy
        Slow(); // wywołanie spowolnienia
        display ++; // zwiększenie wartości do wyświetlenia
    }
    int a = _getch(); // przypisanie wczytanej wartości z klawiatury do zmiennej a
    if(a == 72) // strzałka w górę na klawiaturze
        goto binaryCounterDown_2; // przejście do licznika binarnego zliczającego w dól
    if(a == 80) // strzałka w dół na klawiaturze
        goto pseudoRandomNumberGenerator_9; // przejście do generatora pseudolosowego
    goto binaryCounterUp_1; // kontynuacja danego podprogramu

binaryCounterDown_2: // 8 bitowy licznik binarny zliczający w dół (255…0)
    while( !_kbhit() ) // wciśnięcie przycisku kończy działanie pętli
    {
        printf("\r                                                                          ");
        printf("\r[2] 8 bitowy licznik binarny zliczajacy w dol: ");
        IntToBinary(display); // wywołanie funkcji zmieniającej system dziesiętny na system dwójkowy
        Slow(); // wywołanie spowolnienia
        display --; // zmniejszenie wartości do wyświetlenia
    }
    int b = _getch(); // przypisanie wczytanej wartości z klawiatury do zmiennej b
    if(b == 72) // strzałka w górę na klawiaturze
    {
        counter = 0; // wyzerowanie licznika w przypadku przejścia do innego rodzaju licznika
        goto binaryGrayCounterUp_3; // przejście do licznika kodu graya
    }
    if(b == 80) // strzałka w dół na klawiaturze
        goto binaryCounterUp_1; // przejście do licznika binarnego zliczającego w górę
    goto binaryCounterDown_2; // kontynuacja danego podprogramu

binaryGrayCounterUp_3: // 8 bitowy licznik w kodzie Graya zliczający w górę (repr. 0…255)
    while( !_kbhit() ) // wciśnięcie przycisku kończy działanie pętli
    {
       display = IntToGray(counter); // wywołanie funkcji odpowiedzialnej za konwersję na kod greya
       printf("\r");
       printf("[3] 8 bitowy licznik w kodzie Graya zliczajacy w gore: ");
       IntToBinary(display); // wywołanie funkcji zmieniającej system dziesiętny na system dwójkowy
       Slow(); // wywołanie spowolnienia
       counter ++; // zwiększenie stanu licznika
    }
    int c = _getch(); // przypisanie wczytanej wartości z klawiatury do zmiennej c
    if(c == 72) // strzałka w górę na klawiaturze
        goto binaryGrayCounterDown_4; // przejście do licznika kodu graya zliczającego w dół
    if(c == 80) // strzałka w dół na klawiaturze
    {
        display=0; // zerowanie licznika w przypadku przejścia innego rodzaju licznika
        goto binaryCounterDown_2; // przejście do licznika binarnego zliczającego w dół
    }
    goto binaryGrayCounterUp_3; // kontynuacja danego podprogramu

binaryGrayCounterDown_4: // 8 bitowy licznik w kodzie Graya zliczający w dół (repr. 255…0)
    while( !_kbhit() ) // wciśnięcie przycisku kończy działanie pętli
    {
       display = IntToGray(counter); // wywołanie funkcji odpowiedzialnej za konwersję na kod greya
       printf("\r                                                                          ");
       printf("\r[4] 8 bitowy licznik w kodzie Graya zliczajacy w dol: ");
       IntToBinary(display); // wywołanie funkcji zmieniającej system dziesiętny na system dwójkowy
       Slow(); // wywołanie spowolnienia
       counter --; // zmniejszenie stanu licznika
    }
    int d = _getch(); // przypisanie wczytanej wartości z klawiatury do zmiennej d
    if(d == 72) // strzałka w górę na klawiaturze
        {
            counterBCD = 0; // zerowanie licznika w przypadku przejścia do innego rodzaju licznika
            goto BCDounterUp_5; // przejście do licznika kodu BCD
        }
    if(d == 80) // strzałka w dół na klawiaturze
        goto binaryGrayCounterUp_3; // przejście do licznika kodu graya zliczającego w górę
    goto binaryGrayCounterDown_4; // kontynuacja danego podprogramu

BCDounterUp_5: // 2x4 bitowy licznik w kodzie BCD zliczający w górę (0…99)
    while( !_kbhit() ) // wciśnięcie przycisku kończy działanie pętli
    {
        if(counterBCD > 99) // zabezpiecza licznik przed wartościami niedozwolonymi
            counterBCD = 0; // zerowanie licznika
        display = IntToBCD(counterBCD); // wywołanie funkcji odpowiedzialnej za konwersję na kod BCD
        printf("\r[5] 2x4 bitowy licznik w kodzie BCD zliczajacy w gore: %d ", counterBCD);
        IntToBinary(display); // wywołanie funkcji zmieniającej system dziesiętny na system dwójkowy
        Slow(); // wywołanie spowolnienia
        counterBCD++; // zwiększenie stanu licznika
    }
    int e = _getch(); // przypisanie wczytanej wartości z klawiatury do zmiennej e
    if(e == 72) // strzałka w górę na klawiaturze
        goto BCDounterDown_6; // przejście do licznika BCD zliczającego w dół
    if(e == 80) // strzałka w dół na klawiaturze
        {
            counter=0; // wyzerowanie licznika
            goto binaryGrayCounterDown_4; // przejście do licznika kodu graya zliczającego w dół
        }
    goto BCDounterUp_5; // kontynuacja danego podprogramu

BCDounterDown_6: // 2x4 bitowy licznik w kodzie BCD zliczający w dół (99…0)
    while( !_kbhit() ) // wciśnięcie przycisku kończy działanie pętli
    {
        if(counterBCD > 99) // zabezpiecza licznik przed wartościami niedozwolonymi
            counterBCD = 99; // przypisanie wartości maksymalnej
        display = IntToBCD(counterBCD); // wywołanie funkcji odpowiedzialnej za konwersję na kod BCD
        printf("\r[6] 2x4 bitowy licznik w kodzie BCD zliczajacy w dol: %d ", counterBCD);
        IntToBinary(display); // wywołanie funkcji zmieniającej system dziesiętny na system dwójkowy
        Slow(); // wywołanie spowolnienia
        counterBCD--; // zmniejszenie stanu licznika
    }
    int f = _getch(); // przypisanie wczytanej wartości z klawiatury do zmiennej f
    if(f == 72) // strzałka w górę na klawiaturze
        goto ThreeBitSnake_7; // przejście do 3 bitowego wężyka
    if(f == 80) // strzałka w dół na klawiaturze
        goto BCDounterUp_5; // przejście do licznika BCD zliczającego w górę
    goto BCDounterDown_6; // kontynuacja danego podprogramu

ThreeBitSnake_7: // 3 bitowy wężyk poruszający się lewo-prawo
    while( !_kbhit() ) // wciśnięcie przycisku kończy działanie pętli
    {
        for(int i=0; i<6; i++) // pętla odpowiada za przejście w lewą stronę
        {   
            if( !_kbhit() ) // wciśnięcie przycisku kończy działanie instrukcji warunkowej
            {
                printf("\r                                                                          ");
                printf("\r[7] 3 bitowy wezyk poruszajacy sie lewo-prawo: ");
                IntToBinary(7 << i); // przesuwamy się o i bitów za każdym razem w lewo
                Slow(); // wywołanie spowolnienia
            }
        }
        for(int i=1; i<5; i++) // pętla odpowiada za przejście w prawą stronę
        {
            if( !_kbhit() ) // wciśnięcie przycisku kończy działanie instrukcji warunkowej
            {
                printf("\r                                                                          ");
                printf("\r[7] 3 bitowy wezyk poruszajacy sie lewo-prawo: ");
                IntToBinary(224 >> i); // przesuwamy się o i bitów za każdym razem w prawo
                Slow(); // wywołanie spowolnienia
            }
        }
    }
    int g = _getch(); // przypisanie wczytanej wartości z klawiatury do zmiennej g
    if(g == 72) // strzałka w górę na klawiaturze
        goto queue_8; // przejście do kolejki
    if(g == 80) // strzałka w dół na klawiaturze
    {
        counterBCD = 0; // zerowanie licznika w przypadku przejścia do BCD
        goto BCDounterDown_6; // przejście do licznika BCD zliczającego w dół
    }
    goto ThreeBitSnake_7; // kontynuacja danego podprogramu

queue_8: // Kolejka
    while( !_kbhit() ) // wciśnięcie przycisku kończy działanie pętli
    {
        int number = 1; // wartość początkowa kolejki
        int tmp; // zmienna tymczasowa
        int lastNumer; // ostatnia jedynka z lewej strony pozyskiwana w każdej iteracji
        int ones = 0; // zmienna odpowiedzialna za przechowywanie jedynek
        for(int i=8; i>0; i--) // pętla odpowiada za zakres ruchu w lewą stronę
        {
            for(int j=0; j<i; j++) // pętla odpowiada z ruch w lewą stronę
            {
                if( !_kbhit() ) // wciśnięcie przycisku kończy działanie instrukcji warunkowej
                {
                    printf("\r                                                                          ");
                    printf("\r[8] Kolejka: ");
                    IntToBinary((number << j) | ones); // wypisanie obecnego stanu kolejki
                    Slow(); // wywołanie spowolnienia
                    tmp = j; // zmienna zapamiętuję lokalizacje ostatniej jedynki
                }
            }
            if( !_kbhit() ) // wciśnięcie przycisku kończy działanie instrukcji warunkowej
            {
                lastNumer = number << tmp; // pozyskanie ostatniej jedynki z lewej strony
                ones = ones | lastNumer; // zapamiętanie jedynek do zmiennej
            }
        }
    }
    int h = _getch(); // przypisanie wczytanej wartości z klawiatury do zmiennej h
    if(h == 72) // strzałka w górę na klawiaturze
        goto pseudoRandomNumberGenerator_9; // przejście do generatora liczb pseudolosowych
    if(h == 80) // strzałka w dół na klawiaturze
        goto ThreeBitSnake_7; // przejście do 3 bitowego wężyka
    goto queue_8; // kontynuacja danego podprogramu

pseudoRandomNumberGenerator_9: // 6 bitowy generator liczb pseudolosowych oparty o konfigurację 1110011
    while( !_kbhit() ) // wciśnięcie przycisku kończy działanie pętli
    {
        int seed = 0b1110011; // seed dla generatora
        int number = 1; // liczba, od której generator zaczyna pracę
        int highestBitNumber = 6; // najstarszy bit czyli pierwszy od lewej
        
        printf("\r[9] 6 bitowy generator liczb pseudolosowych: ");
        for(int i = highestBitNumber-1; i >= 0; i--) // służy do przejścia po binarnym zapisie 1
                printf("%d", (number>>i) & 1); // wyświetlenie wszystkich bitów poczynając od 
                                                // lewej strony
        printf("    decimal: %d", number); // wyświetlenie liczby, od której generator zaczyna pracę
        Slow(); // wywołanie spowolnienia
        do
        {
            int tmp = 0; // zmienna tymczasowa
            for(int j = 0; j < highestBitNumber; j++) // służy do przejścia po binarnym zapisie seeda
                if((seed>>j) & 1) // szukanie 1 w seedzie
                    tmp = tmp ^ ((number>>j) & 1); // w przypadku znalezienia poprzednia wartość tmp ^
                    // z odpowiednim bitem z liczby i przypisywana do tmp

            number = (number | (tmp<<highestBitNumber))>>1; // ustalenie nowej wartości liczby
            printf("\r[9] 6 bitowy generator liczb pseudolosowych: ");
            for(int k = highestBitNumber-1; k >= 0; k--) // służy do przejścia po binarnym zapisie liczby
                    printf("%d", (number>>k) & 1); // wyświetlenie pojedynczego bitu poczynając od lewej strony
            printf("    decimal: %d", number); // wyświetlenie wygenerowanej liczby w systemie dziesiętnym
            Slow(); // wywołanie spowolnienia
        }
        while( !_kbhit() ); // moment, w którym generator dotarł do liczby początkowej
    }
    int i = _getch(); // przypisanie wczytanej wartości z klawiatury do zmiennej i
    if(i == 72) // strzałka w górę na klawiaturze
    {
        display=0; // zerowanie licznika w przypadku przejścia do licznika binarnego
                   // zliczającego w górę
        goto binaryCounterUp_1; // przejście licznika binarnego zliczającego w górę
    }
    if(i == 80) // strzałka w dół na klawiaturze
        goto queue_8; // przejście do kolejki    
    goto pseudoRandomNumberGenerator_9; // kontynuacja danego podprogramu
}