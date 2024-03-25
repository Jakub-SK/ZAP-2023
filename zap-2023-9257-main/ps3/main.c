#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hangman.h"

int main(void)
{
    char secret[30];

    srand(time(NULL)); 
    hangman(secret);

    printf("\n\nEnd of the game!\n\n");
    return 0;
}