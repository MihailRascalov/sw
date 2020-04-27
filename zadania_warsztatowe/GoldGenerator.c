#include <stdio.h>

int main()
{
    GoldGenerator();
}

GoldGenerator()
{
    int seedOne = 0b1011011; // seed dla pierwszego generatora
    int seedTwo = 0b1100111; // seed dla drugiego generatora
    int numberOne = 1; // liczba z jaką zaczyna pracę generator numer jeden
    int numberTwo = 1; // liczba z jaką zaczyna pracę generator numer dwa
    int highestBitNumber = 6; // najstarszy bit czyli pierwszy od lewej
    int numberOfIteration = 128; // ilość cykli, którą wykonają generatory

    printf("%d\n", (numberOne & 1) ^ (numberTwo & 1));
    int counter = 0; // licznik odpowiedzialny za zliczanie wykonanych cykli generatora
    do
    {
        int tmpOne = 0; // zmienna tymczasowa numer jeden
        int tmpTwo = 0; // zmienna tymczasowa numer dwa
        for(int j = 0; j < highestBitNumber; j++) // służy do przejściu po binarnym zapisie seeda
        {
            if((seedOne>>j) & 1) // szukanie 1 w pierwszym seedzie
                tmpOne = tmpOne ^ ((numberOne>>j) & 1); // w przypadku znalezienia poprzednia wartość tmp 
                // jest xorowana z odpowiednim bitem z pierwszej liczby i przypisywana do tmpOne
            if((seedTwo>>j) & 1) // szukanie 1 w drugim seedzie
                tmpTwo = tmpTwo ^ ((numberTwo>>j) & 1); // w przypadku znalezienia poprzednia wartość tmp 
                // jest xorowana z odpowiednim bitem z drugiej liczby i przypisywana do tmpTwo
        }
        numberOne = (numberOne | (tmpOne<<highestBitNumber))>>1; // ustalenie nowej wartości numberOne
        numberTwo = (numberTwo | (tmpTwo<<highestBitNumber))>>1; // ustalenie nowej wartości numberTwo
        printf("%d\n", (numberOne & 1) ^ (numberTwo & 1)); // wyświetlenie operacji XOR najmodszego bitu numberOne i numberTwo
        counter++; // zwiększenie licznika o jeden
    }
    while(counter < numberOfIteration); // warunek kończący działanie pętli
}