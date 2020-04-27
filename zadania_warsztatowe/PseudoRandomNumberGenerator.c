#include <stdio.h>

int main()
{
    PseudoRandomNumberGenerator();
}

PseudoRandomNumberGenerator()
{
    int seed = 0b1011011; // seed dla generatora
    int number = 1; // liczba od, której generator zaczyna pracę
    int highestBitNumber = 6; // najstarszy bit czyli pierwszy od lewej

    for(int i = highestBitNumber-1; i >= 0; i--) // służy do przejściu po binarnym zapisie 1
        printf("%d", (number>>i) & 1); // wyświetlenie wszystkich bitów poczynając od lewej strony
    printf("    decimal: %d\n", number); // wyświetlenie liczby od, której generator zaczyna pracę
    do
    {
        int tmp = 0; // zmienna tymczasowa
        for(int j = 0; j < highestBitNumber; j++) // służy do przejściu po binarnym zapisie seeda
            if((seed>>j) & 1) // szukanie 1 w seedzie
                tmp = tmp ^ ((number>>j) & 1); // w przypadku znalezienia poprzednia wartość tmp
                // jest xorowana z odpowiednim bitem z liczby i przypisywana do tmp

        number = (number | (tmp<<highestBitNumber))>>1; // ustalenie nowej wartości liczby
        for(int k = highestBitNumber-1; k >= 0; k--) // służy do przejściu po binarnym zapisie liczby
            printf("%d", (number>>k) & 1); // wyświetlenie pojedynczego bitu poczynając od lewej strony
        printf("    decimal: %d\n", number); // wyświetlenie wygenerowanej liczby w systemie dziesiętnym
    }
    while(number != 1); // moment, w którym generator dotarł do liczby początkowej
}