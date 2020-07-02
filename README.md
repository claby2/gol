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
$ make example-compile
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
    board.nextStep(); // Update with next step with rule_string B3/S23
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
$ make test-compile
```
Run the tests with:
```
$ make test
```

## Reference

[Documentation](DOCUMENTATION.md)

### Functions

| Function                                                | Use
|---------------------------------------------------------|------------------------------------------------------|
| [initRandom](DOCUMENTATION.md#initRandom)               | Initialize random seed                               |
| [getRandomBool](DOCUMENTATION.md#getRandomBool)         | Return a random bool                                 |
| [getBirthValues](DOCUMENTATION.md#getBirthValues)       | Return birth values from B/S notation rule string    |
| [getSurvivalValues](DOCUMENTATION.md#getSurvivalValues) | Return survival values from B/S notation rule string |
| [isValidRuleString](DOCUMENTATION.md#isValidRuleString) | Test whether rule string is valid                    |

### Board Member Functions

| Function                                                        | Use
|-----------------------------------------------------------------|----------------------------------------------------------|
| [(constructor)](DOCUMENTATION.md#(constructor))                 | Construct Game of Life board                             |
| [operator[]](DOCUMENTATION.md#operator[])                       | Access element                                           |
| [height](DOCUMENTATION.md#height)                               | Return the number of rows                                |
| [width](DOCUMENTATION.md#width)                                 | Return the number of columns                             |
| [countNeighborsMoore](DOCUMENTATION.md#countNeighborsMoore)     | Return number of true cells in Moore neighborhood        |
| [countNeighborsNeumann](DOCUMENTATION.md#countNeighborsNeumann) | Return number of true cells in von Neumann neighborhood  |
| [nextStep](DOCUMENTATION.md#nextStep)                           | Iterate to next time step                                |
| [setWrap](DOCUMENTATION.md#setWrap)                             | Set to toggle wrapping for counting neighbors            |
| [getWrap](DOCUMENTATION.md#getWrap)                             | Return the current wrap state                            |
| [getNeighborhoodType](DOCUMENTATION.md#getNeighborhoodType)     | Return current neighborhood type                         |
| [setFromFile](DOCUMENTATION.md#setFromFile)                     | Set values of board from given file                      |
| [getLiveCount](DOCUMENTATION.md#getLiveCount)                   | Return the number of true elements                       |
| [getDeadCount](DOCUMENTATION.md#getDeadCount)                   | Return the number of false elements                      |
| [setFromRLEFile](DOCUMENTATION.md#setFromRLEFile)               | Set values of board from given RLE file                  |
| [setRuleString](DOCUMENTATION.md#setRuleString)                 | Set rule string                                          |
| [getRuleString](DOCUMENTATION.md#getRuleString)                 | Return current rule string                               |
| [saveAsFile](DOCUMENTATION.md#saveAsFile)                       | Save board as file                                       |
| [saveAsRLEFile](DOCUMENTATION.md#saveAsRLEFile)                 | Save board as RLE file                                   |