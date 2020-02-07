#include <iostream>
#include <string>
std::string double_down = "\n\n";
enum Player {COMPUTER, HUMAN};

/* 
    prints game board with current state
*/
void print_board(char *board) {
    std::cout << " " << board[0] << " " << board[1] << " " << board[2] << " \n"
            " " << board[3] << " " << board[4] << " " << board[5] << " \n"
            " " << board[6] << " " << board[7] << " " << board[8] + double_down;
}
/* 
   prints welcome screen at start of game
*/
void print_welcome() {
    std::cout << "Welcome To Tic Tac Toe\n"
            " Use the below numbers to choose a space:\n"
            " 0 1 2 \n"
            " 3 4 5 \n"
            " 6 7 8 \n" + double_down;
}

/* 
   checks if a selection position is a valid move
   parameters: the board
   return: true or false
*/
bool valid_move(char *board, int position) {    
    return (position >= 0 && position <= 8 && board[position] == '_');
}

/* 
   computer ai for defensive block
   parameters: the board
   return: int - position to block
*/
int computer_ai_block(char *board, Player player_1) {
    char opponent_symbol = '_';

    if (player_1 == HUMAN) {
        opponent_symbol = 'X';
    } else {
        opponent_symbol = 'O';
    }

    if ((board[0] == board[1]) && (board[1] == opponent_symbol) && (board[2] == '_')) {
        return 2;
    } else if ((board[0] == board[2]) && (board[2] == opponent_symbol) && (board[1] == '_')) {
        return 1;
    } else if ((board[1] == board[2]) && (board[2] == opponent_symbol) && (board[0] == '_')) {
        return 0;
    } else if ((board[3] == board[4]) && (board[4] == opponent_symbol) && (board[5] == '_')) {
        return 5;
    } else if ((board[3] == board[5]) && (board[5] == opponent_symbol) && (board[4] == '_')) {
        return 4;
    } else if ((board[4] == board[5]) && (board[5] == opponent_symbol) && (board[3] == '_')) {
        return 3;
    } else if ((board[6] == board[7]) && (board[7] == opponent_symbol) && (board[8] == '_')) {
        return 8;
    } else if ((board[6] == board[8]) && (board[8] == opponent_symbol) && (board[7] == '_')) {
        return 7;
    } else if ((board[7] == board[8]) && (board[8] == opponent_symbol) && (board[6] == '_')) {
        return 6;
    } else if ((board[0] == board[3]) && (board[3] == opponent_symbol) && (board[6] == '_')) {
        return 6;
    } else if ((board[0] == board[6]) && (board[6] == opponent_symbol) && (board[3] == '_')) {
        return 3;
    } else if ((board[3] == board[6]) && (board[6] == opponent_symbol) && (board[0] == '_')) {
        return 0;
    } else if ((board[1] == board[4]) && (board[4] == opponent_symbol) && (board[7] == '_')) {
        return 7;
    } else if ((board[1] == board[7]) && (board[7] == opponent_symbol) && (board[4] == '_')) {
        return 4;
    } else if ((board[4] == board[7]) && (board[7] == opponent_symbol) && (board[1] == '_')) {
        return 1;
    } else if ((board[2] == board[5]) && (board[5] == opponent_symbol) && (board[8] == '_')) {
        return 8;
    } else if ((board[2] == board[8]) && (board[8] == opponent_symbol) && (board[5] == '_')) {
        return 5;
    } else if ((board[5] == board[8]) && (board[8] == opponent_symbol) && (board[2] == '_')) {
        return 2;
    } 
    return -1;
}

/* 
   computer logic for picking position - currently just random
   parameters: the board
   return: position
*/
int computer_turn(char *board, Player player_1) {
    int defensive_move = -1;
    defensive_move = computer_ai_block(board, player_1);
    if (defensive_move == -1) {
        int position = rand() % 9;
        while (!valid_move(board, position)) {
            position = rand() % 9; 
        }
        std::cout << position;
        return position;
    } else {
        std::cout << defensive_move;
        return defensive_move;
    }
}

/* 
   check board for winner
   parameters: the board
   return: '_' for no winner or 'X' or 'O' for winner
*/
char check_winner(char *board) {
    if ((board[0] == board[1]) && (board[1] == board[2])) {
        return board[0];
    } else if ((board[3] == board[4]) && (board[4] == board[5])) {
        return board[3];
    } else if ((board[6] == board[7]) && (board[7] == board[8])) {
        return board[6];
    } else if ((board[0] == board[3]) && (board[3] == board[6])) {
         return board[0];       
    }  else if ((board[1] == board[4]) && (board[4] == board[7])) {
         return board[1];       
    }  else if ((board[2] == board[5]) && (board[5] == board[8])) {
         return board[2];       
    }  else if ((board[0] == board[4]) && (board[4] == board[8])) {
         return board[0];       
    }  else if ((board[2] == board[4]) && (board[4] == board[8])) {
        return board[2];        
    }   else {
        return '_';
    }
}

/* 
   check board for tie
   parameters: the board
   return: true or false
*/
char check_tie(char *board) {    
    if (board[0] == '_') {
        return false;
    } else if (board[1] == '_') {
        return false;
    } else if (board[2] == '_') {
        return false;
    } else if (board[3] == '_') {
        return false;
    } else if (board[4] == '_') {
        return false;
    } else if (board[5] == '_') {
        return false;
    } else if (board[6] == '_') {
        return false;
    } else if (board[7] == '_') {
        return false;
    } else if (board[8] == '_') {
        return false;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    
    Player player_1 = HUMAN;
    Player current_player = HUMAN;
    std::string go_first_answer = "";    
    int position = -1;
    char board[9] = {'_','_','_','_','_','_','_','_','_'};
    bool game_over = false;
    bool move_completed = false;
    char current_symbol = 'X';
    char winner = '_';
    bool is_tie = false;

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
        if (current_player == player_1) {
            current_symbol = 'X';
        } else {
            current_symbol = 'O';
        }
        if (current_player == COMPUTER) {  
            board[computer_turn(board, player_1)] = current_symbol;
            current_player = HUMAN;
            std::cout << "Computer Turn" << std::endl;
        } else {            
            move_completed = false;
            while (!move_completed) {
                std::cout << "Pick a Position from 0-8 : \n >> ";
                std::cin >> position;
                std::cout << std::endl;
                if (valid_move(board, position)) {
                    board[position] = current_symbol;     
                    move_completed = true;
                    current_player = COMPUTER;
                    std::cout << "Your Selection" << std::endl;
                } else {
                    std::cout << "Move is not Valid!" << std::endl;
                }
            }
        }
        print_board(board);   
        winner = check_winner(board); 
             
        if (winner != '_') {
            std::cout << "winner is " << winner << std::endl;
            game_over = true;
        }  
        
        is_tie = check_tie(board);  
        if (is_tie == true) {
            std::cout << "Tie Game" << std::endl;
            game_over = true;
        }

    }
    
    return 0;
}
