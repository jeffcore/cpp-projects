#include <iostream>
#include <string>
std::string double_down = "\n\n";

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
   computer logic for picking position - currently just random
   parameters: the board
   return: position
*/
int computer_turn(char *board) {
    int position = rand() % 9;
    while (!valid_move(board, position)) {
        position = rand() % 9; 
    }
    return position;
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

int main(int argc, const char * argv[]) {
    enum player {COMPUTER, HUMAN};
    player player_1 = HUMAN;
    player current_player = HUMAN;
    std::string go_first_answer = "";    
    int position = -1;
    char board[9] = {'_','_','_','_','_','_','_','_','_'};
    bool game_over = false;
    bool move_completed = false;
    char current_symbol = 'X';

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
            board[computer_turn(board)] = current_symbol;
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
        char winner = check_winner(board);        
        if (winner != '_') {
            std::cout << "winner is " << winner << std::endl;
            game_over = true;
        }    
    }
    
    return 0;
}
