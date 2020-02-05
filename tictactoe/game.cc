#include <iostream>
#include <string>
using namespace std;

void print_board(char *board) {
    cout << "Board \n"
            " " << board[0] << " " << board[1] << " " << board[2] << " \n"
            " " << board[3] << " " << board[4] << " " << board[5] << " \n"
            " " << board[6] << " " << board[7] << " " << board[8] << endl;
}
void print_welcome() {
    cout << "Welcome To Tic Tac Toe\n"
            " Use the below numbers to choose a space:\n"
            " 0 1 2 \n"
            " 3 4 5 \n"
            " 6 7 8 " << endl;
}

bool valid_move(char *board, int position) {    
    return (position >= 0 && position <= 8 && board[position] == 'O');
}

int computer_turn(char *board) {
    int position = rand() % 9;
    while (!valid_move(board, position)) {
        position = rand() % 9; 
    }
}

int main(int argc, const char * argv[]) {
    enum player {COMPUTER, HUMAN};
    string answer = "";
    int position = -1;
    char board[9] = {'_','_','_','_','_','_','_','_','_'};
    player player_1 = HUMAN;
    player current_player = HUMAN;
    bool game_over = false;

    print_welcome();
    cout << "Do you want to go first? ( y / n) ";
    cin >> answer;
    if (answer == "n") {        
        player_1 = COMPUTER;
        current_player = COMPUTER;
    }
    cout << player_1;
    cout << "You choose " << answer << "\n";
    print_board(board);

    while(!game_over) {
        if (current_player == COMPUTER) {            
            board[computer_turn(board)] = 'X';
        } else {
            while (!valid_move(board, position)) {
                cout << "Pick a Position from 0-8 : \n >> ";
                cin >> position;
                 board[position] = 'O';
            }
        }
        
    }
    
    cout << "position " << position << endl;

    board[position] = 'X';
    print_board(board);

    return 0;
}
