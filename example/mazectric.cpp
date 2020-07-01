// This example implements a maze rule known as mazectric "B3/S1234"
// The board is first randomized and iterated 50 times
// This results in a maze

#include "../single_include/gol/gol.hpp"

#include <iostream>

int main() {
    gol::initRandom();

    size_t board_height = 50;
    size_t board_width = 50;
    int iterations = 50;
    std::string rule_string = "B3/S1234"; // Mazectric rule string

    gol::Board board(board_height, board_width);

    board.setRuleString(rule_string); // Set mazectric rule string

    // Randomize initial board values
    for(int i = 0; i < board.height(); i++) {
        for(int j = 0; j < board.width(); j++) {
            board[i][j] = gol::getRandomBool();
        }
    }

    // Iterate
    for(int i = 0; i < iterations; i++) {
        board.nextStep();
    }

    // Print with 'O' and '.' characters representing alive and dead cells respectively
    for(int i = 0; i < board.height(); i++) {
        for(int j = 0; j < board.width(); j++) {
            if(board[i][j]) {
                std::cout << 'O' << " ";
            } else {
                std::cout << '.' << " ";
            }
        }
        std::cout << "\n";
    }
}

// Here is an example:
// . . . . . . O O O O O O . . . . . O O . O . O . O . . O . O . O . O . . . . . O O O O O O O O . . O 
// O O O O O O . . . . . . . O O O O . . O O . O . O O . O . O . O . O O O O . O . . . . . . . . O O . 
// . . . . . O . O O O O O O . . . O O O . . O O . O . . O . O . O . . . . O . O . O O O O O O O O . O 
// . O O O O . O . . . . . . O O O . . O . O . . . O O O O . . . O . O O . O . O . O . . . . . . O . O 
// . O . . O . O O . O O O O . . O O O O . O O O O . . . . O . . O . . . . O . O . O O O O O O . O . O 
// . . O O . . . . . . . . . O . O . . . O . . . . O O O O O . . . O O O . . . O . O . . . . . . O . O
// O O . . O O O O O O O . . O . O . O . O . O O O O . . . . O O O . . O . O . O . O O O O O O O O . O 
// . . . O . . . . . . . O . O . O . O . O . . . . . O O O O . . . O . O . O . . . . . . . . . . . . . 
// O O . O . O O O O O O O . O . O . O . . O O O O O . . . O . O . O . O . O O O O O O O O O O O O O . 
// . . . O . O . . . . . . . O O O . O . . . . . . . O . . O . O . . . O . . . . . . . . . . . . . . . 
// O O O O . O O O O O O O O . . . O . O O O O O O O O O O O . O O O O . O O O O O O O O O O O O O O O 
// . . . O O . . . . . . . O . O O O . O . . . . . O . . . O . . . . O . O . . . . . . . . . . . . . . 
// . O . . . O O O O O O O . O . . . . O . O O O . O . O . O O O O . O . O O O O O O O O O O O O O . O
// . O O O O . . . . . . O . . O O O . O . O . O . O . O . . . . . O O . . . . . . . . . . . . . O . O 
// . . O . O . O O . O . . O O . . O . O . O . O . O . O O O O O . . . O O O O O O O O O O O O . . . O 
// O . O . O . . O . O O O . . O O O . O . O . . . O . O . . . . O O O . . . . . O . O . . . . O O O .
// O . O . O . O O . . . . . O . . . . O . O O O O O . O . O O O . . . O O O O . O . O . O O . O . . . 
// O . O O . O . O O O O O O O O O O O O O . O . O . . O . . . . O O . . . . O . O . O . O O . O O . O 
// . . . . O . . . . . . . . . . . . . . . . O . O . O . O O O O O . O O O O . . O . O O . . O . . . . 
// O O O . O . O O . O O O O . O O O O O O O O . O . O . . . . . . . . . . O . O O . . . O . O . O O O 
// . . O . O . . O . O . . O . O . O . . . . . . O . O O O O O O O O O O . O . O . O O O O . O . O . .
// O . O . O . O O . O O . O . O . O . O . O O O . . . . . . . . . . . O . O . O . O . . . . O . O . O 
// O . O . O . O . O . O . O . O . O O O . O . O O O O O O O O O O O . O . O . O . O O O O . O . O . . 
// O . O . O O . . O . O . O O O . . . . . O . . . . . . . . . . . O . O . O . O . . . . O . O . O O O 
// . . O . . . O O O . O . . . . O O O O O . O O O O O O O O . O O O . O . O O . O O O O O . . . . . . 
// O O O O O O . O . . O O O O . O . . . O O O . . . . . . O . O . . O . O . O . . . . . O . O . . O O 
// . . . . . . . . O O . . . O . . O O . . . . O O O . O . O . O . O O . O . O . O O O . O . O . O . . 
// O O O O O O O O . . O O O . O . O . O O O O . . O . O . O . O . . . . O . O . . O O O O . O . O . O 
// . . . . . . . O O O O . O . O . O . . . . O O O O . O . O . O . O O . O . O O . . . . . O O . O . . 
// O O O O O O . . . . . O O . O . . O O O . O . . O . O . O . O . O O . O . O O . O O O . . O . O . O 
// . . . . . O O O O O . O . O . O . O . . . O O O O . O . O . O . . . . O . . O . O . O O . . . O . O 
// O O O O O . . . . O . O . O . O . . . O O . . . . O O O O . O O O O O . O . O . O . . . O O O O . O 
// . . . . . . O O O O . O . O . O . . . . O . O O . O . . . . . . . . O . O . O . . . O O . . . O . O
// O O O O O O O . . . O . O . O . O . O . O . O . O O . O O O O O O O O . O . O O O O . O . O . O . .
// . . . . . . . O O . O . O . O . O . O . O . O . O . O . O . . . . . O . O . . . . . . O . O . O O O
// . O O O O O O . O . O . O . O . O . O . O . O . O . O . O . O O O . O . O O O O O O O O O O . . . .
// O . O . . . . . O . O . . . O . O . O O O . O . O . O . O . O . O . O . . . . . . . . . . . O O O O
// O . O . O O O . . . O O O O O . O . . . . . O . O . O . O . O . O . . O O O O O O O O O O . O . . .
// . O O O O . O O O O . . . . . . O O O O O O O . O . O . O . O . O O O . . . . . . . . . O . O . O O
// O . . . . . . . . . O O O O O O . . . . . . O . O . O . O . O . O . . . O O O O O O O . . . . O . O
// O . O O O O O O O O . . . . . . O O O O O O O . O . O . O . O . O O O O . . . . . . . O O O . O . .
// O . . . . . . . . O O O O O O . . . . . . O . O . O O . O . O . . . . . . O O O O O O . . O . O O O
// O . O O O O O O . O . . . . . O O O . O . O . O . O . O O . O O O O O O . O . O . O . O O . O . . .
// O . . . . . . . . O O O O O . O . O . O . O . O . O . O . . . . . O . O . O . O . O . O . . O . O .
// O O O O O O O O . . . . . . O . . O . O . O . O . O . O O O O O . O . O . O . O . O . O O O O . O .
// . . . O . O . . O O O . O . O . O O . O . O . O . O . . . . . . . O . O . . . O . O . . . . . . O .
// O O . O . . O . O . O . O . O . O . . O . O . O . . O O O O O O O . O . . O . O . O O O O O O O . O
// . O O O O O O . O . . . O . O . O . O . O . O . O . O . . . . . . . O O . O . O . . . . . . . O . O
// O . . . . . . . O O O O O . O . O . O . . . O . O . O . O O O O O O O . . O . O . O O O O O . O O .
// O O O O O O O . . . . . O . . O O . O . O . O . O . O O . O . . . O . . O O . O . . . . . . O . O .