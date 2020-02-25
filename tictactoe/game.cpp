#include <iostream>
#include <string>
#include <ctime>
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
   check board is empty
   parameters: the board
   return: true false
*/
bool is_board_empty(char *board) {
    if (board[0] != '_') {
        return false;
    } else if (board[1] != '_') {
        return false;
    } else if (board[2] != '_') {
        return false;
    } else if (board[3] != '_') {
        return false;
    } else if (board[4] != '_') {
        return false;
    } else if (board[5] != '_') {
        return false;
    } else if (board[6] != '_') {
        return false;
    } else if (board[7] != '_') {
        return false;
    } else if (board[8] != '_') {
        return false;
    }
    return true;
}

/* 
   computer ai for defensive block
   parameters: the board
   return: int - position to block
   todo: make a 2 array off all position iterate through it [[0,1,2], [0,2,1]]
   todo: refactor board check to another function, the reuse for winning move check
*/
int computer_ai(char *board, Player player_1) {
    char opponent_symbol = 'O';
    char computer_symbol = 'X';
    int board_checks[24][3] = {
        {0,1,2}, {0,2,1}, {1,2,0},
        {3,4,5}, {3,5,4}, {4,5,3},
        {6,7,8}, {6,8,7}, {7,8,6},
        {0,3,6}, {0,6,3}, {3,6,0},
        {1,4,7}, {1,7,4}, {4,7,1},
        {2,5,8}, {2,8,5}, {5,8,2},
        {0,4,8}, {4,8,0}, {0,8,4},
        {2,4,6}, {4,6,2}, {2,6,4}       
    };

    //switch X O if human is ready player one
    if (player_1 == HUMAN) {
        opponent_symbol = 'X';
        computer_symbol = 'O';
    } 

    //check for winning position
    for (int i = 0; i < 24; i++) {       
        // std::cout << board_checks[i][0] << board_checks[i][1] << board_checks[i][2]<< std::endl;
        if ((board[board_checks[i][0]] == board[board_checks[i][1]]) && 
            (board[board_checks[i][1]] == computer_symbol) && 
            (board[board_checks[i][2]] == '_')) {
            return board_checks[i][2];
        }        
    }

    //check for blocking position
    for (int i = 0; i < 24; i++) {       
        // std::cout << board_checks[i][0] << board_checks[i][1] << board_checks[i][2]<< std::endl;
        if ((board[board_checks[i][0]] == board[board_checks[i][1]]) && 
            (board[board_checks[i][1]] == opponent_symbol) && 
            (board[board_checks[i][2]] == '_')) {
            return board_checks[i][2];
        }        
    }

    return -1;
}

/* 
   computer logic for picking position - currently just random
   parameters: the board
   return: position
*/
int computer_turn(char *board, Player player_1) {
    int ai_move = -1;
    srand(time(NULL));
    int rand_position = -1;    
    int corner_moves[4] = {0,2,6,8};

    // if computer opening move pick random corner - best first move
    if (is_board_empty(board)) {
        while (true) {
            rand_position = rand() % 9;
            for (int i = 0; i < 4; i++) {
                if (rand_position == corner_moves[i]) {
                    return rand_position;
                }
            }
        }
    }

    ai_move = computer_ai(board, player_1);
    if (ai_move == -1) {
        rand_position = rand() % 9;
        while (!valid_move(board, rand_position)) {
            rand_position = rand() % 9; 
        }
        std::cout << rand_position;
        return rand_position;
    } else {        
        return ai_move;
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
    }  else if ((board[2] == board[4]) && (board[4] == board[6])) {
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
        // set symbol of current player
        if (current_player == player_1) {
            current_symbol = 'X';
        } else {
            current_symbol = 'O';
        }

        // computer or human turn
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
