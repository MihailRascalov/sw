#include <stdio.h>

int main()
{
    BitShiftLeftOrRight(6, 1, 'R'); // wywołanie funkcji celem wykonania 6 >> 1
}

void BitShiftLeftOrRight(int numberToShift, int howMuchToShift, char direction)
{
    if(direction == 'R' || direction == 'r') // sprawdzenie czy przesunięcie w prawo
        printf("%d >> %d = %d", numberToShift, howMuchToShift, numberToShift >> howMuchToShift); 
        // wyświetlenie wyniku operacji przesunięcia
    else if (direction == 'L' || direction == 'l') // sprawdzenie czy przesunięcie w lewo
        printf("%d << %d = %d", numberToShift, howMuchToShift, numberToShift << howMuchToShift);
        // wyświetlenie wyniku operacji przesunięcia
    else // jeżeli znak jest inny niż R, r, L lub l
        printf("Wrong direction."); // wyświetlenie powiadomienia o złym kierunku
}