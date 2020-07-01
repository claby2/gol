// Implements a 60P312 oscillator and steps 614 times
// 60P312 oscillators have a period of 312 
// The initial values of the board are read from a file

#include "../single_include/gol/gol.hpp"

#include <iostream>

gol::Board board(42, 42);

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

    // Make 60P312 oscillator
    board.setFromFile("board_files/60P312.txt");

    for(int i = 0; i < 614; i++) {
        printAndStep();
    }

}