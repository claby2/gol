# gol Documentation

## Functions


### initRandom() <a name = "initRandom"></a>

Initialize random seed.

Call this function in main and call it once to use random functions such as `getRandomBool()` .


### getRandomBool() <a name = "getRandomBool"></a>

Return a random bool.

Assign the return value of this function to a board cell. The board cell will either be true or false. The function requires `initRandom()` to be called once.

#### Example of getRandomBool
Here is an example of setting the board with randomized bool values:
```cpp
#include <gol/gol.hpp>

int main() {
    gol::initRandom(); // Initialize random seed

    gol::Board board(10, 10); // Construct Game of Life board

    for(int i = 0; i < board.height(); i++) {
        for(int j = 0; j < board.width(); j++) {
            board[i][j] = gol::getRandomBool(); // Return a random bool
        }
    }
}
```


### getBirthValues(rule_string) <a name = "getBirthValues"></a>

Return birth values from B/S notation rule string.

The `rule_string` parameter specifies the rule string in [B/S notation](https://www.conwaylife.com/wiki/Rulestring#B.2FS_notation). For example, the rule string for Conway's Game of Life is `B3/S23`. The `rule_string` argument should be a string.

The function parses the given rule string and returns the birth values as a string. 


### getSurvivalValues(rule_string) <a name = "getSurvivalValues"></a>

Return survival values from B/S notation rule string.

The `rule_string` parameter specifies the rule string in [B/S notation](https://www.conwaylife.com/wiki/Rulestring#B.2FS_notation). For example, the rule string for Conway's Game of Life is `B3/S23`. The `rule_string` argument should be a string.

The function parses the given rule string and returns the survival values as a string. 


### isValidRuleString(rule_string) <a name = "isValidRuleString"></a>

Test whether rule string is valid.

The `rule_string` parameter specifies the rule string in [B/S notation](https://www.conwaylife.com/wiki/Rulestring#B.2FS_notation). For example, the rule string for Conway's Game of Life is `B3/S23`. The `rule_string` argument should be a string.

The function returns a bool. If it returns true, it means the `rule_string` argument is valid.

The function validates the `rule_string` in lower case by making sure the following conditions are met:
* There is exactly one occurrence of the char `b`
* There is exactly one occurrence of the char `s`
* There is exactly one occurrence of the char `/`
* The only chars that are present are `b/s123456789`

If one of these conditions is met, the function returns false.


## Board Member Functions


### (constructor) <a name = "(constructor)"></a>

Construct Game of Life board.

The board needs to be constructed before using member functions. The dimensions of the board are required to construct the board. As a result, it takes two arguments:
* The number of `rows` as a size_t
* The number of `columns` as a size_t

The constructor also initializes the buffer board.

#### Example of (constructor)
Here is an example of constructing the board with 5 rows and 10 columns:
```cpp
#include <gol/gol.hpp>

int main() {
    gol::Board board(5, 10); // Construct Game of Life board
}
```


### operator[n] <a name = "operator[]"></a>

Access element.

Operator overload to access elements of the board. Although the board is stored as a one-dimensional pointer array, accessing the board is done as if it was a two-dimensional array.

The operator takes an argument `n` indicating the position of an element on the board. This uses zero-based numbering.

#### Example of operator[n]
Here is an example of accessing elements:
```cpp
#include <gol/gol.hpp>
#include <iostream>

int main() {
    gol::Board board(5, 10); // Construct Game of Life board
    board[0][1] = true;
    if(board[0][1]) {
        std::cout << "board[0][1] is true" << '\n';
    }
}
```


### board.height() <a name = "height"></a>

Return the number of rows.

The return type is size_t.


### board.width() <a name = "width"></a>

Return the number of columns.

The return type is size_t.


### board.countNeighborsMoore(x, y) <a name = "countNeighborsMoore"></a>

Return number of true cells in Moore neighborhood.

This method returns an int that represents the number of neighbors with a value of true a given cell has. This is done by counting the number of true cells in a [Moore neighborhood](https://en.wikipedia.org/wiki/Moore_neighborhood).

The arguments `x` and `y` should be of type int. The arguments `x` and `y` represents the column and row of a specified cell respectively. These use zero-based numbering.

The method reads from the buffer board and not the actual board.


### board.countNeighborsNeumann(x, y) <a name = "countNeighborsNeumann"></a>

Return number of true cells in von Neumann neighborhood.

This method returns an int that represents the number of neighbors with a value of true a given cell has. This is done by counting the number of true cells in a [von Neumann neighborhood](https://en.wikipedia.org/wiki/Von_Neumann_neighborhood).

The arguments `x` and `y` should be of type int. The arguments `x` and `y` represents the column and row of a specified cell respectively. These use zero-based numbering.

The method reads from the buffer board and not the actual board.


### board.nextStep(rule_string) <a name = "nextStep"></a>

Iterate to next time step.

This method iterates the board by a time step. It calls the `countNeighbors*` methods for each cell and assigns it a value which is dependent on the given rule string.

The `rule_string` parameter specifies the rule string in [B/S notation](https://www.conwaylife.com/wiki/Rulestring#B.2FS_notation). For example, the rule string for Conway's Game of Life is `B3/S23`. The `rule_string` argument should be a string.

After this method is called, the values of the board will be updated.

#### Example of board.nextStep(rule_string)
Here is a program which prints and steps 4 times:
```cpp
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


### board.setWrap(state) <a name = "setWrap"></a>

Set to toggle wrapping for counting neighbors.

Each board has a wrapping state which represents if the board should wrap around. For example, this means that if a cell is located on the leftmost column, the neighbor counting functions would include neighboring cells on the rightmost column.

The wrapping state has a default value of true. This means that if board wrapping is intentional, this method does not need to be called.

The method takes one argument `state`. This should be a bool which represents whether wrapping should be enabled or not.

#### Example of board.setWrap(state)
Here is a program that disables board wrapping:
```cpp
#include <gol/gol.hpp>

int main() {
    Board board(10, 10);
    board.setWrap(false);
    // Wrapping is now disabled
}
```

### board.getWrap() <a name = "setWrap"></a>

Return the current wrap state.

This method returns a bool. The return value indicates whether wrapping is enabled or disabled as true or false respectively.


### board.getNeighborhoodType() <a name = "getNeighborhoodType"></a>

Return current neighborhood type.

This method returns a string representing the current neighborhood type. This can be either `"moore"` or `"neumann"` representing a [Moore neighborhood](https://en.wikipedia.org/wiki/Moore_neighborhood) or a [von Neumann neighborhood](https://en.wikipedia.org/wiki/Von_Neumann_neighborhood) respectively.