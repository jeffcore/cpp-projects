#include <iostream>
#include <string>
const int BOARD_ROWS = 6;
const int BOARD_COLUMNS = 7;

void move(char board[BOARD_ROWS][BOARD_COLUMNS], int column, char piece) {
    int col_index = column - 1;
    if (board[0][col_index] != '_') {
        std::cout << "Column Filled - Invalid Move" << std::endl;
        return;
    }
    for (int i = 0; i < BOARD_ROWS; i++){
        if (board[i][col_index] != '_') {                        
            board[i-1][col_index] = piece;
            break;
        }
        if (i == BOARD_ROWS - 1) {
            board[i][col_index] = piece;            
            break;
        }
    }
}

void print_board(char board[BOARD_ROWS][BOARD_COLUMNS]) {
    // print board
    std::string board_print = "";
    int temp_row = 0;
    for (int i = 0; i < BOARD_ROWS; i++){
        if (i != temp_row){
            board_print = board_print + "\n";
            temp_row = i;
        } 
        for (int j = 0; j < BOARD_COLUMNS; j++){
            board_print = board_print + " " + board[i][j];
        }       
    }
    std::cout << board_print << std::endl;
}

void valid_moves(char board[BOARD_ROWS][BOARD_COLUMNS]) {
    // board always starts with bottom row as available moves
    int moves[BOARD_COLUMNS];
    for (int i = 0; i < BOARD_COLUMNS; ++i){
        moves[i] = BOARD_ROWS - 1;
    }

    // loop through board by each column - looking for bottom open spot
    for (int i = 0; i < BOARD_COLUMNS; i++){        
        for (int j = 0; j < BOARD_ROWS; j++){            
            if (board[j][i] != '_') {     
                if (j == 0){
                    moves[i] = -1;
                } else if (moves[i] > j - 1) {
                    moves[i] = j - 1;
                }
            }
        }       
    }
    for (int i = 0; i < 7; i++){   
        std::cout << moves[i]<< std::endl;
    }    
}

int main() {    
    char board[BOARD_ROWS][BOARD_COLUMNS];

    // fill board
    for (int i = 0; i < BOARD_ROWS; i++){
        for (int j = 0; j < BOARD_COLUMNS; j++){
            board[i][j] = '_';
        }
    }   
    
    move(board, 1, 'X');
    move(board, 3, 'X');
    move(board, 3, 'X');
    move(board, 2, 'O');
    move(board, 1, 'X');
    move(board, 1, 'X');
    move(board, 1, 'O'); 
    move(board, 1, 'O'); 
    move(board, 1, 'O'); 
    print_board(board);
    valid_moves(board);
    return 0;
}
