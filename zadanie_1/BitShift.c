#include <stdio.h>

int main()
{
    BitShiftLeftOrRight(6, 1, 'R');
}

void BitShiftLeftOrRight(int numberToShift, int howMuchToShift, char direction)
{
    if(direction == 'R' || direction == 'r')
        printf("%d >> %d = %d", numberToShift, howMuchToShift, numberToShift >> howMuchToShift);
    else if (direction == 'L' || direction == 'l')
        printf("%d << %d = %d", numberToShift, howMuchToShift, numberToShift << howMuchToShift);
    else
        printf("Wrong direction.");
}