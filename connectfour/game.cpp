#include <iostream>
#include <string>
const int BOARD_ROWS = 6;
const int BOARD_COLUMNS = 7;
enum Player {COMPUTER, HUMAN};

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
    std::cout << " Use the below numbers to choose a space:\n"
        " 1 2 3 4 5 6 7\n";

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

int* valid_moves(char board[BOARD_ROWS][BOARD_COLUMNS]) {
    // board always starts with bottom row as available moves
    int moves[BOARD_COLUMNS];
    for (int i = 0; i < BOARD_COLUMNS; ++i){
        moves[i] = BOARD_ROWS - 1;
    }

    // loop through board by each column -
    //   looking for bottom open spot
    for (int i = 0; i < BOARD_COLUMNS; i++){        
        for (int j = 0; j < BOARD_ROWS; j++){            
            if (board[j][i] != '_') {     
                if (j == 0){
                    moves[i] = -1;
                } else  {
                    moves[i] = j - 1;
                }
                break;
            }
        }       
    }
    for (int i = 0; i < BOARD_COLUMNS; i++){   
        std::cout << moves[i] << " ";
    }    
    std::cout << " \n" << std::endl;
    return moves;
}

bool is_move_valid(char board[BOARD_ROWS][BOARD_COLUMNS], int move) {
    int *moves = valid_moves(board);
    
    if (((move >= 1) and (move <= 7)) && (moves[move-1] != -1)) {
        return true;
    } else {
        return false;
    }
}

int check_for_winner(char board[BOARD_ROWS][BOARD_COLUMNS]) {
    bool current_match = false;
    int count_same = 1;
    const int DIAGONAL_POSITIONS = 6;
    int rows_diagonal[DIAGONAL_POSITIONS] = {0,0,0,0,1,2};
    int columns_diagonal[DIAGONAL_POSITIONS] = {3,2,1,0,0,0};    
    int columns_diagonal_front[DIAGONAL_POSITIONS] = {3,4,5,6,6,6};
    int row_index = 0;
    int column_index = 0;


    for (int i = 0; i < 6; i++) {    
        current_match = false;
        count_same = 1;
        row_index = rows_diagonal[i];
        column_index = columns_diagonal[i];

        //check for diagonal left to right
        while ((row_index < BOARD_ROWS-1) && (column_index < BOARD_COLUMNS-1)) {
            // std::cout << "row idex " << row_index << " column index " << column_index << " " << board[row_index][column_index] << std::endl;

            if ((board[row_index][column_index] == board[row_index+1][column_index+1]) && 
                    (board[row_index][column_index] == 'X')) {
                // std::cout << "got match";
                current_match = true;
                count_same += 1;
            } else {
                current_match = false;
                count_same = 1;
            }
            
            if ((current_match == true) && (count_same == 4)) {
                return 1;
            }

            row_index += 1;
            column_index += 1;

        }
        // std::cout << " \n" << std::endl;

        current_match = false;
        count_same = 1;
        row_index = rows_diagonal[i];
        column_index = columns_diagonal_front[i];
        //check for diagonal  right to left
        while ((row_index < BOARD_ROWS-1) && (column_index > 0)) {
            // std::cout << "row idex " << row_index << " column index " << column_index << " " << board[row_index][column_index] << std::endl;           
            
            if ((board[row_index][column_index] == board[row_index+1][column_index-1]) && 
                    (board[row_index][column_index] == 'X')) {
                // std::cout << "got match";
                current_match = true;
                count_same += 1;
            } else {
                current_match = false;
                count_same = 1;
            }

            if ((current_match == true) && (count_same == 4)) {
                return 1;
            }
            
            row_index += 1;
            column_index -= 1;
        }
        // std::cout << " \n" << std::endl;
    }

    current_match = false;
    count_same = 1;
    // check for winner by column
    for (int i = 0; i < BOARD_COLUMNS; i++){        
        for (int j = 0; j < BOARD_ROWS; j++){    
            if ((current_match == true) && (count_same == 4)) {
                return 1;
            }
            if ((board[j][i] == board[j+1][i]) && (board[j+1][i] == 'X')) {
                current_match = true;
                count_same += 1;
            } else {
                current_match = false;
                count_same = 1;
            }
            // std::cout << "i" << i << "j" << j << std::endl;            
        }       
    }

    // check for winner by rows
    current_match = false;
    count_same = 1;
    for (int i = 0; i < BOARD_ROWS; i++){        
        for (int j = 0; j < BOARD_COLUMNS; j++){    
            if ((current_match == true) && (count_same == 4)) {
                return 1;
            }
            if ((board[i][j] == board[i][j+1]) && (board[i][j+1] == 'X')) {
                current_match = true;
                count_same += 1;
            } else {
                current_match = false;
                count_same = 1;
            }
            // std::cout << "i" << i << "j" << j << std::endl;            
        }       
    }
    
    return 0;
}


void tests(char board[BOARD_ROWS][BOARD_COLUMNS]) {
    // test winner horizontal
    move(board, 1, 'X');
    move(board, 2, 'X');
    move(board, 3, 'X');
    move(board, 4, 'X');
    if (check_for_winner(board))  {
        std::cout << "Pass" << std::endl;
    }
    
    move(board, 3, 'X');
    move(board, 6, 'X');
    move(board, 2, 'O');
    move(board, 5, 'X');
    print_board(board);
    std::cout << "winner " << check_for_winner(board);
    valid_moves(board);
    move(board, 1, 'O'); 
    move(board, 1, 'O'); 
    move(board, 2, 'O');
  
    move(board, 1, 'X');
    print_board(board);
    std::cout << "winner " << check_for_winner(board);
    valid_moves(board);
    move(board, 1, 'X');
    move(board, 1, 'X'); 
    move(board, 5, 'X');
    move(board, 4, 'X');
    move(board, 1, 'X');
    move(board, 5, 'X');
    move(board, 4, 'X');
    move(board, 6, 'X');
    move(board, 6, 'X');
    move(board, 6, 'X');
    move(board, 2, 'X');
    move(board, 2, 'X');
    print_board(board);
    valid_moves(board);
}

/* 
   prints welcome screen at start of game
*/
void print_welcome() {
    std::cout << "Welcome To Connect 4\n\n"
            " Use the below numbers to choose a space:\n"
            " 1 2 3 4 5 6 7\n"
            " _ _ _ _ _ _ _\n"
            " _ _ _ _ _ _ _\n"
            " _ _ _ _ _ _ _\n"
            " _ _ _ _ _ _ _\n"
            " _ _ _ _ _ _ _\n"
            " _ _ _ _ _ _ _\n\n";
}

int main() {    
    Player player_1 = HUMAN;
    Player current_player = HUMAN;
    std::string go_first_answer = ""; 
    int position = -1;
    bool game_over = false;
    bool move_completed = false;
    char current_symbol = 'X';
    char winner = '_';
    bool is_tie = false;
    char board[BOARD_ROWS][BOARD_COLUMNS];    
    // fill board
    for (int i = 0; i < BOARD_ROWS; i++){
        for (int j = 0; j < BOARD_COLUMNS; j++){
            board[i][j] = '_';
        }
    }   
    
    print_welcome();

    std::cout << "Do you want to go first? \n (y / n) >> ";
    std::cin >> go_first_answer;
    if (go_first_answer == "n") {        
        player_1 = COMPUTER;
        current_player = COMPUTER;
    }
    std::cout << std::endl;

    print_board(board);

    while(!game_over) {
        // set symbol of current player
        if (current_player == player_1) {
            current_symbol = 'X';
        } else {
            current_symbol = 'O';
        }
        
        if (current_player == COMPUTER) {  
            // board[computer_turn(board, player_1)] = current_symbol;
            current_player = HUMAN;
            // std::cout << "Computer Turn" << std::endl;
        } else {            
            move_completed = false;
            while (!move_completed) {
                std::cout << "Pick a Position from 1-7 : \n >> ";
                std::cin >> position;
                std::cout << std::endl;
                if (is_move_valid(board, position)) {
                    move(board, position, current_symbol);      
                    move_completed = true;
                    current_player = COMPUTER;
                    std::cout << "Your Selection" << std::endl;
                } else {
                    std::cout << "Move is not Valid!" << std::endl;
                }                
            }           
        }
        print_board(board);   
        winner = check_for_winner(board); 
        if (winner) {
            std::cout << "winner is " << winner << std::endl;
            game_over = true;
        }  
    
    }

    // tests(board);
    return 0;
}
