#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void IntToBinary(unsigned char input)
{
    short i = 7;
    while(i>=0)
    {
        printf("%d",(input >> i) & 1);
        i--;
    }
    printf("   ");
}

void Slow()
{
    int c,d = 0;
    for (c = 1; c <= 32767; c++)
        for (d = 1; d <= 8192; d++)
        {}
}

unsigned char IntToGray(unsigned char input)
{
    return input ^ (input >> 1);
}

int main(void)
{
unsigned char display=0;
unsigned char counter = 0;

binaryCounterUp_1:
    while( !_kbhit() )
    {
        printf("\r                        ");
        printf("\r");
        IntToBinary(display);
        Slow();
        display ++;
    }
    int a = _getch();
    if(a == 72) // up
        goto binaryCounterDown_2;
    if(a == 80) // down
        goto pseudoRandomNumberGenerator_9;
    goto binaryCounterUp_1;

binaryCounterDown_2:
    while( !_kbhit() )
    {
        printf("\r");
        IntToBinary(display);
        Slow();
        display --;
    }
    int b = _getch();
    if(b == 72) // up
    {
        counter = 0;
        goto binaryGrayCounterUp_3;
    }
    if(b == 80) // down
        goto binaryCounterUp_1;
    goto binaryCounterDown_2;

binaryGrayCounterUp_3:
    while( !_kbhit() )
    {
       display = IntToGray(counter);
       printf("\r");
       IntToBinary(display);
       Slow();
       counter ++;
    }
    int c = _getch();
    if(c == 72) // up
        goto binaryGrayCounterDown_4;
    if(c == 80) // down
    {
        display=0;
        goto binaryCounterDown_2;
    }
    goto binaryGrayCounterUp_3;

binaryGrayCounterDown_4:
    while( !_kbhit() )
    {
       display = IntToGray(counter);
       printf("\r");
       IntToBinary(display);
       Slow();
       counter --;
    }
    int d = _getch();
    if(d == 72) // up
        goto BCDounterUp_5;
    if(d == 80) // down
        goto binaryGrayCounterUp_3;
    goto binaryGrayCounterDown_4;

BCDounterUp_5:
    while( !_kbhit() )
    {
        printf("\r");
        printf("BCDounterUp_5 no implementation");
        Slow();
        goto BCDounterUp_5;
    }
    int e = _getch();
    if(e == 72) // up
        goto BCDounterDown_6;
    if(e == 80) // down
        {
            counter=0;
            goto binaryGrayCounterDown_4;
        }
    goto BCDounterUp_5;

BCDounterDown_6:
    while( !_kbhit() )
    {
        printf("\r");
        printf("BCDounterDown_6 no implementation");
        Slow();
        goto BCDounterDown_6;
    }
    int f = _getch();
    if(f == 72) // up
        goto ThreeBitSnake_7;
    if(f == 80) // down
        goto BCDounterUp_5;
    goto BCDounterDown_6;

ThreeBitSnake_7:
    while( !_kbhit() )
    {
        printf("\r");
        printf("3BitSnake_7 no implementation");
        Slow();
        goto ThreeBitSnake_7;
    }
    int g = _getch();
    if(g == 72) // up
        goto queue_8;
    if(g == 80) // down
        goto BCDounterDown_6;
    goto ThreeBitSnake_7;

queue_8:
    while( !_kbhit() )
    {
        printf("\r");
        printf("queue_8 no implementation");
        Slow();
        goto queue_8;
    }
    int h = _getch();
    if(h == 72) // up
        goto pseudoRandomNumberGenerator_9;
    if(h == 80) // down
        goto ThreeBitSnake_7;
    goto queue_8;

pseudoRandomNumberGenerator_9:
    while( !_kbhit() )
    {
        int seed = 0b1110011; // seed dla generatora
        int number = 1; // liczba, od której generator zaczyna pracę
        int highestBitNumber = 6; // najstarszy bit czyli pierwszy od lewej
        
        printf("\r");
        for(int i = highestBitNumber-1; i >= 0; i--) // służy do przejścia po binarnym zapisie 1
                printf("%d", (number>>i) & 1); // wyświetlenie wszystkich bitów poczynając od 
                                                // lewej strony
        printf("    decimal: %d", number); // wyświetlenie liczby, od której generator zaczyna pracę
        Slow();
        do
        {
            int tmp = 0; // zmienna tymczasowa
            for(int j = 0; j < highestBitNumber; j++) // służy do przejścia po binarnym zapisie seeda
                if((seed>>j) & 1) // szukanie 1 w seedzie
                    tmp = tmp ^ ((number>>j) & 1); // w przypadku znalezienia poprzednia wartość tmp ^
                    // z odpowiednim bitem z liczby i przypisywana do tmp

            number = (number | (tmp<<highestBitNumber))>>1; // ustalenie nowej wartości liczby
            printf("\r");
            for(int k = highestBitNumber-1; k >= 0; k--) // służy do przejścia po binarnym zapisie liczby
                    printf("%d", (number>>k) & 1); // wyświetlenie pojedynczego bitu poczynając od lewej strony
            printf("    decimal: %d", number); // wyświetlenie wygenerowanej liczby w systemie dziesiętnym
            Slow();
        }
        while( !_kbhit() ); // moment, w którym generator dotarł do liczby początkowej
        // goto pseudoRandomNumberGenerator_9;
    }
    int i = _getch();
    if(i == 72) // up
    {
        display=0;
        goto binaryCounterUp_1;
    }
    if(i == 80) // down
        goto queue_8;    
    goto pseudoRandomNumberGenerator_9;
    //goto queue_8;
}