// Initialize a board and fill it with random bool values

#include "../single_include/gol/gol.hpp"

#include <iostream>

int main() {
    gol::initRandom(); // Initialize random seed

    gol::Board board(10, 10); // Construct Game of Life board

    for(int i = 0; i < board.height(); i++) {
        for(int j = 0; j < board.width(); j++) {
            board[i][j] = gol::getRandomBool(); // Return a random bool
        }
    }

    for(int i = 0; i < board.height(); i++) {
        for(int j = 0; j < board.width(); j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }

}