# gol Documentation

## Table of Contents

Functions:

+ [initRandom](#initRandom)
+ [getRandomBool](#getRandomBool)
+ [getBirthValues](#getBirthValues)
+ [getSurvivalValues](#getSurvivalValues)
+ [isValidRuleString](#isValidRuleString)

Board Member Functions:

+ [(constructor)](#(constructor))
+ [operator[]](#operator[])
+ [height](#height)
+ [width](#width)
+ [countNeighborsMoore](#countNeighborsMoore)
+ [countNeighborsNeumann](#countNeighborsNeumann)
+ [nextStep](#nextStep)
+ [setWrap](#setWrap)
+ [getWrap](#getWrap)
+ [getNeighborhoodType](#getNeighborhoodType)
+ [setFromFile](#setFromFile)
+ [getLiveCount](#getLiveCount)
+ [getDeadCount](#getDeadCount)
+ [setFromRLEFile](#setFromRLEFile)
+ [setRuleString](#setRuleString)
+ [getRuleString](#getRuleString)
+ [saveAsFile](#saveAsFile)
+ [saveAsRLEFile](#saveAsRLEFile)

## Functions

### initRandom() <a name = "initRandom"></a>

Initialize random seed.

Call this function in main and call it once to use random functions such as `getRandomBool()` .

### getRandomBool() <a name = "getRandomBool"></a>

Return a random bool.

Assign the return value of this function to a board cell. The board cell will either be true or false. The function requires `initRandom()` to be called once.

#### Example of getRandomBool()
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

+ There is exactly one occurrence of the char `b`
+ There is exactly one occurrence of the char `s`
+ There is exactly one occurrence of the char `/`
+ The only chars that are present are `b/s123456789`

If one of these conditions is not met, the function returns false.

## Board Member Functions

### (constructor) <a name = "(constructor)"></a>

Construct Game of Life board.

The board needs to be constructed before using member functions. The dimensions of the board are required to construct the board. As a result, it takes two arguments:

+ The number of `rows` as a size_t
+ The number of `columns` as a size_t

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
    } else {
        std::cout << "This will not print" << '\n';
    }
}
```

### board.height() <a name = "height"></a>

Return the number of rows.

The return type is size_t.

### board.width() <a name = "width"></a>

Return the number of columns.

The return type is size_t.

### board.countNeighborsMoore(x, y, [copy_board_to_buffer]) <a name = "countNeighborsMoore"></a>

Return number of true cells in Moore neighborhood.

This method returns an int that represents the number of neighbors with a value of true a given cell has. This is done by counting the number of true cells in a [Moore neighborhood](https://en.wikipedia.org/wiki/Moore_neighborhood).

The arguments `x` and `y` should be of type int. The arguments `x` and `y` represents the column and row of a specified cell respectively. These use zero-based numbering.

The method takes an additional but optional argument `copy_board_to_buffer`. This is of type bool which defaults to true. If this argument is set to false, the board will not be copied to the buffer board where the counting is executed.

### board.countNeighborsNeumann(x, y, [copy_board_to_buffer]) <a name = "countNeighborsNeumann"></a>

Return number of true cells in von Neumann neighborhood.

This method returns an int that represents the number of neighbors with a value of true a given cell has. This is done by counting the number of true cells in a [von Neumann neighborhood](https://en.wikipedia.org/wiki/Von_Neumann_neighborhood).

The arguments `x` and `y` should be of type int. The arguments `x` and `y` represents the column and row of a specified cell respectively. These use zero-based numbering.

The method takes an additional but optional argument `copy_board_to_buffer`. This is of type bool which defaults to true. If this argument is set to false, the board will not be copied to the buffer board where the counting is executed.

### board.nextStep() <a name = "nextStep"></a>

Iterate to next time step.

This method iterates the board by a time step. It calls the `countNeighbors*` methods for each cell and assigns it a value which is dependent on the rule string.

After this method is called the values of the board will be updated.

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
    gol::Board board(10, 10);
    board.setWrap(false);
    // Wrapping is now disabled
}
```

### board.getWrap() <a name = "getWrap"></a>

Return the current wrap state.

This method returns a bool. The return value indicates whether wrapping is enabled or disabled as true or false respectively.

### board.getNeighborhoodType() <a name = "getNeighborhoodType"></a>

Return current neighborhood type.

This method returns a string representing the current neighborhood type. This can be either `"moore"` or `"neumann"` representing a [Moore neighborhood](https://en.wikipedia.org/wiki/Moore_neighborhood) or a [von Neumann neighborhood](https://en.wikipedia.org/wiki/Von_Neumann_neighborhood) respectively.

### board.setFromFile(file_path) <a name = "setFromFile"></a>

Set values of board from given file.

This method takes a string argument `file_path`. This file path should represent the relative location of the board file.

The board file should follow a certain format, see the example below.

#### Example of board.setFromFile(file_path)
The first two lines should contain two integers `r` and `c` representing the number of rows and columns of the board. These dimensions should be equal to the dimensions of the board (specified when it is first constructed).

The next `r` lines should contain a set of characters of size `c`. The characters `-`, `0`, and `.` represent dead cells. The characters `x`, `X`, `1`, `o`, and `O` represent living cells. These characters can be used interchangeably.

The file also supports comments at the end of lines. Comments can use any delimiter as long as there is a whitespace between the read value and itself.

This is a valid board file named `board_files/board_file.txt`:

```
5 <- this is the number of rows
9 <- this is the number of columns
-0-------
----0----
---Xx1---
0------0-
----0----
```

In your source file:

```cpp
#include <gol/gol.hpp>

int main() {
    gol::Board board(5, 9); // The dimensions specified here should be the same as in the board file
    board.setFromFile("board_files/board_file.txt");
}
```

The board should hold these values after calling the method:

```
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 1 1 1 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
```

### board.getLiveCount() <a name = "getLiveCount"></a>

Return the number of true elements.

This method counts the number of elements on the board that are true and returns this number as an int.

### board.getDeadCount() <a name = "getDeadCount"></a>

Return the number of false elements.

This method counts the number of elements on the board that are false and returns this number as an int.

### board.setFromRLEFile() <a name = "setFromRLEFile"></a>

Set values of board from given RLE file.

This method takes a string argument `file_path`. This file path should represent the relative location of the [RLE file](https://www.conwaylife.com/wiki/Run_Length_Encoded). The method converts the contents of the RLE file to lower case and strips whitespace. If a `<tag>` in the file holds a value of `b`, it is considered dead; if a `<tag>` holds a value that is not `b`, it assumes that it is an alive cell. This is because the method only supports two states: a cell can only be either alive or dead.

The board file should follow the RLE format, see the example below.

#### Example of board.setFromRLEFile()

This is a valid RLE file named `rle_files/dragon.rle`:

```
#N Dragon
#O Paul Tooke
#C An orthogonal period 6 spaceship. The first c/6 spaceship to be constructed.
#C www.conwaylife.com/wiki/index.php?title=Dragon
x = 29, y = 18, rule = B3/S23
12bo16b$12b2o14bo$10bob2o5bobo4b2ob$5bo3bo3b3o2bo4bo5b$2o3bo2bo6bobo5b
3o2bo$2o3bob2o6bo3bobobo5b$2o3bo10bobo7b2ob$5b2o14bo6bo$7bo12bobo6b$7b
o12bobo6b$5b2o14bo6bo$2o3bo10bobo7b2ob$2o3bob2o6bo3bobobo5b$2o3bo2bo6b
obo5b3o2bo$5bo3bo3b3o2bo4bo5b$10bob2o5bobo4b2ob$12b2o14bo$12bo!
```

In your source file:

```cpp
#include <gol/gol.hpp>

int main() {
    gol::Board board(18, 29); // The dimensions specified here should be the same as in the board file
    board.setFromRLEFile("rle_files/dragon.rle");
}
```

The board should hold these values after calling the method:

```
0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 1 0 1 1 0 0 0 0 0 1 0 1 0 0 0 0 1 1 0
0 0 0 0 0 1 0 0 0 1 0 0 0 1 1 1 0 0 1 0 0 0 0 1 0 0 0 0 0
1 1 0 0 0 1 0 0 1 0 0 0 0 0 0 1 0 1 0 0 0 0 0 1 1 1 0 0 1
1 1 0 0 0 1 0 1 1 0 0 0 0 0 0 1 0 0 0 1 0 1 0 1 0 0 0 0 0
1 1 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 1 1 0
0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 1
0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0
0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 1
1 1 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 1 1 0
1 1 0 0 0 1 0 1 1 0 0 0 0 0 0 1 0 0 0 1 0 1 0 1 0 0 0 0 0
1 1 0 0 0 1 0 0 1 0 0 0 0 0 0 1 0 1 0 0 0 0 0 1 1 1 0 0 1
0 0 0 0 0 1 0 0 0 1 0 0 0 1 1 1 0 0 1 0 0 0 0 1 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 1 0 1 1 0 0 0 0 0 1 0 1 0 0 0 0 1 1 0
0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

### board.setRuleString(rule_string) <a name = "setRuleString"></a>

Set rule string.

This method takes one argument `rule_string` as a string. The rule string will take the value of `rule_string` if it is valid. Validation is done through `isValidRuleString()`. If the `rule_string` is not a valid rule string, an exception will be thrown.

The `rule_string` parameter specifies the rule string in [B/S notation](https://www.conwaylife.com/wiki/Rulestring#B.2FS_notation). For example, the rule string for Conway's Game of Life is `B3/S23`. The `rule_string` argument should be a string.

The default value of the rule string is equal to `"B3/S23"`. This means that calling this method is not necessary if the standard Game of Life rule string is to be used.

#### Example of board.setRuleString(rule_string)
Here is an example of setting the rule string to `B3/S1234`:

```cpp
#include <gol/gol.hpp>

int main() {
    gol::Board board(10, 10); // Construct Game of Life board
    board.setRuleString("B3/S1234");
}
```

### board.getRuleString() <a name = "getRuleString"></a>

Return current rule string.

This method returns the current rule string.

The returned rule string should be in [B/S notation](https://www.conwaylife.com/wiki/Rulestring#B.2FS_notation). For example, the rule string for Conway's Game of Life is `B3/S23`.

### board.saveAsFile(file_path) <a name = "saveAsFile"></a>

Save board as file.

This method takes one argument `file_path` and writes the contents of the board (including its dimensions) to a file. The `file_path` argument should be a string and represent the path to the file to be written. If the file does not exist, a new file will be created. This file format can be read with the method `board.setFromFile(file_path)`.  

#### Example of board.saveAsFile(file_path)

This example reads a file in `.rle` file format and outputs a `.txt` file from it.
`dragon.rle`:

```
#N Dragon
#O Paul Tooke
#C An orthogonal period 6 spaceship. The first c/6 spaceship to be constructed.
#C www.conwaylife.com/wiki/index.php?title=Dragon
x = 29, y = 18, rule = B3/S23
12bo16b$12b2o14bo$10bob2o5bobo4b2ob$5bo3bo3b3o2bo4bo5b$2o3bo2bo6bobo5b
3o2bo$2o3bob2o6bo3bobobo5b$2o3bo10bobo7b2ob$5b2o14bo6bo$7bo12bobo6b$7b
o12bobo6b$5b2o14bo6bo$2o3bo10bobo7b2ob$2o3bob2o6bo3bobobo5b$2o3bo2bo6b
obo5b3o2bo$5bo3bo3b3o2bo4bo5b$10bob2o5bobo4b2ob$12b2o14bo$12bo!
```

Your source file:

```cpp
#include <gol/gol.hpp>

int main() {
    gol::Board board(18, 29); // Construct Game of Life board
    board.setFromRLEFile("dragon.rle"); // Read as RLE file
    board.saveAsFile("output.txt"); // Output and save as .txt file
}
```

`output.txt`:

```
18
29
............O................
............OO..............O
..........O.OO.....O.O....OO.
.....O...O...OOO..O....O.....
OO...O..O......O.O.....OOO..O
OO...O.OO......O...O.O.O.....
OO...O..........O.O.......OO.
.....OO..............O......O
.......O............O.O......
.......O............O.O......
.....OO..............O......O
OO...O..........O.O.......OO.
OO...O.OO......O...O.O.O.....
OO...O..O......O.O.....OOO..O
.....O...O...OOO..O....O.....
..........O.OO.....O.O....OO.
............OO..............O
............O................

```

### board.saveAsRLEFile(file_path) <a name = "saveAsRLEFile"></a>

Save board as RLE file.

This method takes one argument `file_path` and writes the contents of the board (including its dimensions and rule string) to a file in [RLE format](https://www.conwaylife.com/wiki/Run_Length_Encoded). The `file_path` argument should be a string and represent the path to the RLE file to be written. If the RLE file does not exist, a new file will be created. This RLE file format can be read with the method `board.setFromRLEFile(file_path)`.  

Although it is valid to omit some segments of the board, such as dead cells at the end of a pattern line, the file from this method represents all cells. However, the file should still be able to read `.rle` files regardless if expected segments are omitted.

#### Example of board.saveAsRLEFile(file_path)

This example reads a `.txt` file and outputs an `RLE` file from it.
`dragon.txt`:

```
18
29
............O................
............OO..............O
..........O.OO.....O.O....OO.
.....O...O...OOO..O....O.....
OO...O..O......O.O.....OOO..O
OO...O.OO......O...O.O.O.....
OO...O..........O.O.......OO.
.....OO..............O......O
.......O............O.O......
.......O............O.O......
.....OO..............O......O
OO...O..........O.O.......OO.
OO...O.OO......O...O.O.O.....
OO...O..O......O.O.....OOO..O
.....O...O...OOO..O....O.....
..........O.OO.....O.O....OO.
............OO..............O
............O................
```

Your source file:

```cpp
#include <gol/gol.hpp>

int main() {
    gol::Board board(18, 29); // Construct Game of Life board
    board.setFromFile("dragon.txt"); // Read as .txt file
    board.saveAsRLEFile("output.rle"); // Output and save as .rle file
}
```

`output.rle`:

```
x = 29, y = 18, rule = B3/S23
12bo16b$12b2o14bo$10bob2o5bobo4b2ob$5bo3bo3b3o2bo4bo5b$2o3bo2bo6bobo5b
3o2bo$2o3bob2o6bo3bobobo5b$2o3bo10bobo7b2ob$5b2o14bo6bo$7bo12bobo6b$7b
o12bobo6b$5b2o14bo6bo$2o3bo10bobo7b2ob$2o3bob2o6bo3bobobo5b$2o3bo2bo6b
obo5b3o2bo$5bo3bo3b3o2bo4bo5b$10bob2o5bobo4b2ob$12b2o14bo$12bo16b!
```