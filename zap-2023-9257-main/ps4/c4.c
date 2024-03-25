#include <stdio.h>
#include "c4.h"


void initialize_board(int rows, int cols, char board[rows][cols]) {

   for ( int i = 0; i < rows; i++ ) {

        for ( int j = 0; j < cols; j++ ) {

            board[i][j] = '.';

        }

    }

}

void print_board(int rows, int cols, const char board[rows][cols]) {

    int counterC = 1;

    for ( int i = 0; i < rows; i++ ) {

        for ( int j = 0; j < cols; j++ ) {

            printf(" | ");
            printf("%c", board[i][j]);

        }

        printf(" | \n");
    }

    printf("  ---");
    for ( int k = 1; k < cols; k++ ) {

        printf (" ---");
    }

    printf("\n");

    for ( int k = 1; k <= cols; k++ ) {

        printf ("   %d", counterC);
        counterC++;

    }
    printf("\n");

}

int is_board_full(int rows, int cols, const char board[rows][cols]) {

    for ( int i = 0; i < rows; i++ ) {
        for ( int j = 0; j < cols; j++ ) { 
            if ( board[i][j] == '.' ) {
                return 0;
            }
        }
    }

    return 1;
}

int is_valid_move(int rows, int cols, const char board[rows][cols], int col) {

    for ( int i = 0; i < rows; i++ ) {
        if ( board[i][col - 1] == '.' ) {
            return 1;
        }
    }

    return 0;

}

int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece) { 

    if ( !is_valid_move(rows, cols, board, col) ) {

        return 0;

    }

    else {

        for ( int i = rows - 1; i >= 0; i-- ) {
            if ( board[i][col - 1] == '.' ) {
                board[i][col - 1] = player_piece;
                return i;
            }
        }
    }
        return 0;
}