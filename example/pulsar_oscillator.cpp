// Implements a pulsar oscillator and steps 6 times
// pulsar oscillators have a period of 3 

#include "../single_include/gol/gol.hpp"

#include <iostream>

gol::Board board(17, 17);

// Prints the board and then updates with next step
void printAndStep() {
    std::cout << "\n";
    for(int i = 0; i < board.height(); i++) {
        for(int j = 0; j < board.width(); j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
    board.nextStep(); // Update with next step with rule_string B3/S23
}

int main() {

    for(int i = 0; i < board.height(); i++) {
        for(int j = 0; j < board.width(); j++) {
            board[i][j] = false;
        }
    }

    // Make pulsar oscillator
    board[1][5] = true; 
    board[1][11] = true;
    board[2][5] = true;
    board[2][11] = true;
    board[3][5] = true;
    board[3][6] = true;
    board[3][10] = true;
    board[3][11] = true;
    board[5][1] = true;
    board[5][2] = true;
    board[5][3] = true;
    board[5][6] = true;
    board[5][7] = true;
    board[5][9] = true;
    board[5][10] = true;
    board[5][13] = true;
    board[5][14] = true;
    board[5][15] = true;
    board[6][3] = true;
    board[6][5] = true;
    board[6][7] = true;
    board[6][9] = true;
    board[6][11] = true;
    board[6][13] = true;
    board[7][5] = true;
    board[7][6] = true;
    board[7][10] = true;
    board[7][11] = true;
    board[9][5] = true;
    board[9][6] = true;
    board[9][10] = true;
    board[9][11] = true;
    board[10][3] = true;
    board[10][5] = true;
    board[10][7] = true;
    board[10][9] = true;
    board[10][11] = true;
    board[10][13] = true;
    board[11][1] = true;
    board[11][2] = true;
    board[11][3] = true;
    board[11][6] = true;
    board[11][7] = true;
    board[11][9] = true;
    board[11][10] = true;
    board[11][13] = true;
    board[11][14] = true;
    board[11][15] = true;
    board[13][5] = true;
    board[13][6] = true;
    board[13][10] = true;
    board[13][11] = true;
    board[14][5] = true;
    board[14][11] = true;
    board[15][5] = true;
    board[15][11] = true;

    for(int i = 0; i < 6; i++) {
        printAndStep();
    }

}

// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
// 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 
// 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 
// 0 0 0 0 0 1 1 0 0 0 1 1 0 0 0 0 0 
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
// 0 1 1 1 0 0 1 1 0 1 1 0 0 1 1 1 0 
// 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 0 0 
// 0 0 0 0 0 1 1 0 0 0 1 1 0 0 0 0 0 
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 1 1 0 0 0 1 1 0 0 0 0 0
// 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 0 0 
// 0 1 1 1 0 0 1 1 0 1 1 0 0 1 1 1 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 1 1 0 0 0 1 1 0 0 0 0 0 
// 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0
// 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 

// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
// 0 0 0 0 1 1 0 0 0 0 0 1 1 0 0 0 0
// 0 0 0 0 0 1 1 0 0 0 1 1 0 0 0 0 0
// 0 0 1 0 0 1 0 1 0 1 0 1 0 0 1 0 0 
// 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1 0 0
// 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 0 0
// 0 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
// 0 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 0
// 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 0 0
// 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1 0 0
// 0 0 1 0 0 1 0 1 0 1 0 1 0 0 1 0 0 
// 0 0 0 0 0 1 1 0 0 0 1 1 0 0 0 0 0
// 0 0 0 0 1 1 0 0 0 0 0 1 1 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 1 0 0 0 0 1 0 1 0 0 0 0 1 0 0 
// 0 0 1 0 0 0 0 1 0 1 0 0 0 0 1 0 0
// 0 0 1 0 0 0 0 1 0 1 0 0 0 0 1 0 0
// 0 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 0 
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 0 
// 0 0 1 0 0 0 0 1 0 1 0 0 0 0 1 0 0
// 0 0 1 0 0 0 0 1 0 1 0 0 0 0 1 0 0
// 0 0 1 0 0 0 0 1 0 1 0 0 0 0 1 0 0 
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 0 
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0