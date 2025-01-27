#include <stdio.h>

int main()
{
    DecimalToBinary(128); // wywołanie funkcji z liczbą całkowitą do zamiany na kod dwójkowy
}

void DecimalToBinary(int n) // n to liczba całkowita do zamiany na kod dwójkowy
{
    int table[32]; // deklaracja tablicy typu int przechowującej 32 bity
    int i = 0; // deklaracja i inicjalizacja zmiennej odpowiadającej za indeks w tablicy

    do
    {
        table[i] = n&1; // zapisanie w tablicy wyniku koniunkcji bitowej
        n = n >> 1; // przesunięcie bitowe o 1 element w prawo na zmiennej n i przypisanie
                    // do zmiennej n
        i++; // zwiększenie zmiennej i odpowiadającej za indeks w tablicy o 1
    } 
    while (n > 0); // warunek kończący działanie pętli
    int j = i - 1; // odejmujemy od zmiennej i -1 ponieważ tab[i] posiada wartość przypadkową
    for(j; j > -1; j--) // pętla operująca na przedziale koniec-początek tablicy
        printf("%d", table[j]); // wyświetlenie danej wartości tablicy czyli wartości 1 lub 0
}