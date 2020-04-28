#include <stdio.h>
#include <time.h>

int main( void )
{
   while( !_kbhit() )
      _cputs( "Hit me!! " );
      
   printf( "\nKey struck was '%c'\n", _getch() );
}

Queue()
{
    int number = 7;

    for(int i=7; i>=0; i--)
    {
        printf("%d", (number >> i ) & 1);
    } 
    printf("\n");
    number = number << 1;
}