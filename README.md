# gol (Game of Life)
gol is a [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) library for C++.

With gol, you can easily simulate Conway's Game of Life cellular automaton in C++.
gol is a single-file include which means you only need one header file to use it.

## Installation
1. Download the latest [single header version](https://raw.githubusercontent.com/claby2/gol/master/single_include/gol/gol.hpp).
2. Either put the header file in a central location (with a specified path) or directly in your project tree.

## Examples

To compile all the examples:
```
$ cd example
$ make compile
```

### Blinker Oscillator

Here is an implementation that prints a blinker oscillator and steps 4 times:
```cpp
// Implements a blinker oscillator and steps 4 times
// blinker oscillators have a period of 2 

#include <gol/gol.hpp>

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
    board.nextStep("B3/S23"); // Update with next step with rule_string B3/S23
}

int main() {
    for(int i = 0; i < board.height(); i++) {
        for(int j = 0; j < board.width(); j++) {
            board[i][j] = false;
        }
    }

    // Make blinker oscillator
    board[2][2] = true;
    board[2][3] = true;
    board[2][4] = true;

    for(int i = 0; i < 4; i++) {
        printAndStep();
    }
}
```

This will print the following twice:
```
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 
0 0 1 1 1 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 

0 0 0 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 
```

## Testing

Testing requires [Catch2](https://github.com/catchorg/Catch2/).
Compile with:
```
$ cd tests
$ make compile
```
Run the tests with:
```
$ make test
```

## Reference

### Functions

| Function              | Use
|-----------------------|----------------------------------------------------------|
| initRandom            | Initialize random seed                                   |
| getRandomBool         | Return a random bool                                     |
| getBirthValues        | Return birth values from B/S notation rule string        |
| getSurvivalValues     | Return survival values from B/S notation rule string     |
| isValidRuleString     | Test whether rule string is valid                        |

### Board Member Functions

| Function              | Use
|-----------------------|----------------------------------------------------------|
| (constructor)         | Construct Game of Life board                             |
| operator[]            | Access element                                           |
| height                | Return the number of rows                                |
| width                 | Return the number of columns                             |
| countNeighborsMoore   | Return number of true cells in Moore neighborhood        |
| countNeighborsNeumann | Return number of true cells in von Neumann neighborhood  |
| nextStep              | Iterate to next time step                                |
| setWrap               | Set to toggle wrapping for counting neighbors            |
| getWrap               | Return the current wrap state                            |
| getNeighborhoodType   | Return current neighborhood type                         |