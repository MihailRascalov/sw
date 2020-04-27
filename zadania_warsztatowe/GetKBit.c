#include <stdio.h>

int main()
{
    printf("%d", GetKBit(8, 3)); // 8 w systemie dwójkowym to 1000, więc trzeci bit jest
    // równy 1 co zwraca poniższa funkcja
}

int GetKBit(int number, int whichBit)
{
	return (number >> whichBit ) & 1; // przesunięcie liczby number o whichBit miejsc w 
    // prawo, a następnie otrzymany wynik wraz z konikcją bitową i 1 zwraca szukany bit
}