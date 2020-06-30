// Implements a beacon oscillator and steps 4 times
// beacon oscillators have a period of 2 

#include "../single_include/gol/gol.hpp"

#include <iostream>

gol::Board board(10, 10);

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

    // Make beacon oscillator
    board[2][2] = true;
    board[2][3] = true;
    board[3][2] = true;
    board[4][5] = true;
    board[5][4] = true;
    board[5][5] = true;

    for(int i = 0; i < 4; i++) {
        printAndStep();
    }

}

// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 1 1 0 0 0 0 0 0
// 0 0 1 0 0 0 0 0 0 0
// 0 0 0 0 0 1 0 0 0 0
// 0 0 0 0 1 1 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0

// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 1 1 0 0 0 0 0 0
// 0 0 1 1 0 0 0 0 0 0
// 0 0 0 0 1 1 0 0 0 0
// 0 0 0 0 1 1 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0