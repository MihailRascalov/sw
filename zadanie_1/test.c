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

int main(void)
{
unsigned long i;
unsigned char display=0;

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
        goto binaryGrayCounterUp_3;
    if(b == 80) // down
        goto binaryCounterUp_1;
    goto binaryCounterDown_2;

binaryGrayCounterUp_3:
    while( !_kbhit() )
    {
        printf("\r");
        printf("binaryGrayCounterUp_3 no implementation");
        Slow();
        goto binaryGrayCounterUp_3;
    }
    int d = _getch();
    if(d == 72) // up
        goto binaryGrayCounterDown_4;
    if(d == 80) // down
        goto binaryCounterDown_2;
    goto binaryGrayCounterUp_3;

binaryGrayCounterDown_4:
    printf("\r");
    printf("binaryGrayCounterDown_4 no implementation");
    return 0;

queue_8:
    printf("\r");
    printf("queue no implementation");
    return 0;

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
    int c = _getch();
    if(c == 72) // up
    {
        display=0;
        goto binaryCounterUp_1;
    }
        
    if(c == 80) // down
        goto queue_8;    
    goto pseudoRandomNumberGenerator_9;
    //goto queue_8;
}