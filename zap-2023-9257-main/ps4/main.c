#include "ballsortpuzzle.h"
#include "c4.h"

int main() {

    srand( time(NULL) );

    int rows = 4, cols = 5, col = 2;
    char board[rows][cols];
    
    initialize_board(rows, cols, board);
    print_board(rows, cols, board);
    is_board_full(rows, cols, board);
    is_valid_move(rows, cols, board, col);
    ball_sort_puzzle();

    return 0;
}