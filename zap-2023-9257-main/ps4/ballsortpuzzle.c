#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ballsortpuzzle.h"

void generator(const int rows, const int columns, char field[rows][columns]) {

    char symbols[7] = {'+', '@', '*', '^', '#', '$', '%'};

    int i, j, k, n;
    int emptycolumn1, emptycolumn2;
    int counterR = 1, counterC = 1;

    n = 7;

    for (i = 0; i < rows; i++) {
        for (j = n - 1; j > 0; j--) {
            k = rand() % (j + 1);
            char temp = symbols[j];
            symbols[j] = symbols[k];
            symbols[k] = temp;
        }
        for (j = 0; j < columns; j++) {
            field[i][j] = symbols[j % 4];
        }
    }

    for (j = 0; j < columns; j++) {
        for (i = n - 1; i > 0; i--) {
            k = rand() % (i + 1);
            char temp = symbols[i];
            symbols[i] = symbols[k];
            symbols[k] = temp;
        }
        for (i = 0; i < rows; i++) {
            field[i][j] = symbols[i % 4];
        }
    }
    
    emptycolumn1 = rand() % columns;

    do {
        emptycolumn2 = rand() % columns;
    } while (emptycolumn1 == emptycolumn2);

    for (int i = 0; i < rows; i++) {
        field[i][emptycolumn1] = ' ';
        field[i][emptycolumn2] = ' ';
    }

    for ( i = 0; i < rows; i++ ) {

        printf("%d  | ", counterR);

        for ( j = 0; j < columns; j++ ) {

            printf("%c", field[i][j]);
            printf(" | ");

        }

        counterR++;
        printf("\n");
    }

    printf("    ---");
    for ( k = 1; k < columns; k++ ) {

        printf (" ---");
    }


    printf ("\n     %d", counterC);
    counterC++;
                
    for ( k = 1; k < columns; k++ ) {

        printf ("   %d", counterC);
        counterC++;

    }
    printf("\n");
    
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y) {
    
    int i, j, k;
    int counterR = 1, counterC = 1;
    int destinationRow = rows - 1;
    int maxRow = rows - 1;
    int originRow = 0;
    char carrier = ' ';
    x = 0;
    y = 0;

    printf("Select which column you would like to pluck a symbol from.\n");
    scanf("%d", &y);
    printf("Select with column you wish to move the symbol to.\n");
    scanf("%d", &x);

    y = y - 1;
    x = x - 1;

    if (x < 0 || x >= columns || y < 0 || y >= columns) {
        printf("Invalid column indices. Please choose valid columns.\n");
        return;
    }

    if (x == y) {
        printf("Cannot move to the same column. Choose a different column.\n");
        return;
    }

    while (originRow <= maxRow && field[originRow][y] == ' ') {
        originRow++;
    }

    while (destinationRow >= 0 && field[destinationRow][x] != ' ') {
        destinationRow--;
    }

    if (destinationRow < 0) {
        printf("Invalid move: Destination column is full\n");
        return;
    }

    else {
    carrier = field[originRow][y];
    field[destinationRow][x] = carrier;
    field[originRow][y] = ' '; }

    /* redrawing the map after update */

    printf("\n");

 for ( i = 0; i < rows; i++ ) {

        printf("%d  | ", counterR);

        for ( j = 0; j < columns; j++ ) {

            printf("%c", field[i][j]);
            printf(" | ");

        }

        counterR++;
        printf("\n");
    }

    printf("    ---");
    for ( k = 1; k < columns; k++ ) {

        printf (" ---");
    }


    printf ("\n     %d", counterC);
    counterC++;
                
    for ( k = 1; k < columns; k++ ) {

        printf ("   %d", counterC);
        counterC++;

    }
    printf("\n");
} 

bool check(const int rows, const int columns, char field[rows][columns]) {

    for (int col = 0; col < columns; ++col) {
        char currentChar = field[0][col];  
        
        for (int row = 1; row < rows; ++row) {
            
            if (field[row][col] != currentChar) {
                return false;  
            }
        }
    }
    
    return true;
}

void ball_sort_puzzle() { 

    int rows = 0;
    int columns = 0;

    printf("How many rows ?\n");
    scanf("%d", &rows);
    printf("How many columns ?\n");
    scanf("%d", &columns);

    char field[rows][columns];
    int x = 0, y = 0;

    generator(rows, columns, field);

    while ( check(rows, columns, field) != true ) {
            down_possible(rows, columns, field, x, y);
    } 

    if ( check(rows, columns, field) == true ) {
        printf("\nYOU WIN!\n");
    }

}
