#ifndef GOL_HPP
#define GOL_HPP

#include <algorithm>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <time.h>

namespace gol {

    // Initialize random seed
    void initRandom() {
        srand(time(NULL));
    }

    // Return a random bool
    bool getRandomBool() {
        return rand() % 2;
    }

    // Parses a given rule string in B/S notation and returns
    // birth values as a string
    std::string getBirthValues(std::string rule_string) {
        bool start_counting = false;
        std::string birth_values;
        for(auto& c : rule_string) {
            if(c == 'b' || c == 'B') {
                start_counting = true;
            } else if(start_counting && (c == 's' || c == 'S' || c == '/')) {
                start_counting = false;
                break;
            } else if(start_counting) {
                birth_values += c;
            }
        }
        return birth_values;
    }

    // Parses a given rule string in B/S notation and returns
    // survival values as a string
    std::string getSurvivalValues(std::string rule_string) {
        bool start_counting = false;
        std::string survival_values;
        for(auto& c : rule_string) {
            if(c == 's' || c == 'S') {
                start_counting = true;
            } else if(start_counting && (c == 'b' || c == 'B' || c == '/')) {
                start_counting = false;
                break;
            } else if(start_counting) {
                survival_values += c;
            }
        }
        return survival_values;
    }

    // Returns if given rule string follows B/S notation
    // Notation is as follows: B{number list}/S{number list};
    bool isValidRuleString(std::string rule_string) {
        std::transform(rule_string.begin(), rule_string.end(), rule_string.begin(),
            [](unsigned char c){ return std::tolower(c); });
        return 
            (std::count(rule_string.begin(), rule_string.end(), 'b') == 1) && 
            (std::count(rule_string.begin(), rule_string.end(), 's') == 1) && 
            (std::count(rule_string.begin(), rule_string.end(), '/') == 1) &&
            (rule_string.find_first_not_of("b/s123456789") == std::string::npos);
    }

    class BoardException : public std::runtime_error {
        public:
            template<typename... Args>
            BoardException(Args... args) : std::runtime_error(args...) {}
    };

    class Board {
        public:
            struct BoardRow {
                bool * row;
                size_t length;
                bool& operator [](size_t index) {
                    if(index >= length) {
                        throw BoardException("Board index out of bound");
                    }
                    return row[index];
                }
            };

            // Instantiate board with user-specified dimensoins
            Board(size_t rows_, size_t columns_) : rows(rows_), columns(columns_) {
                board = new bool[rows_ * columns_];
                buffer_board = new bool[rows_ * columns_];
            }

            BoardRow operator [](size_t index) {
                BoardRow row = {
                    &board[index * columns],
                    columns
                };
                return row;
            }

            // Returns the number of rows in the board
            size_t height() {
                return rows;
            }

            // Returns the number of columns in the board
            size_t width() {
                return columns;
            }

            // Counts neighbors as a Moore neighborhood. Eight
            // neighbors are analysed for their state.
            int countNeighborsMoore(int x, int y) {
                int number_of_neighbors = 0;
                for(int i = 0; i < 8; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if(nx < 0 || ny < 0) continue;
                    if(nx >= columns || ny >= rows) continue;
                    if(buffer_board[ny * columns + nx]) number_of_neighbors++;
                }
                return number_of_neighbors;
            }

            // Counts neighbors as a Von Neumann neighborhood. Four
            // neighbors are analysed for their state.
            int countNeighborsNeumann(int x, int y) {
                int number_of_neighbors = 0;
                for(int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if(nx < 0 || ny < 0) continue;
                    if(nx >= columns || ny >= rows) continue;
                    if(buffer_board[ny * columns + nx]) number_of_neighbors++;
                }
                return number_of_neighbors;
            }

            // Iterate to the next time step with a given rule string
            void nextStep(std::string rule_string_ = "B3/S23") {
                if(!isValidRuleString(rule_string_)) {
                    throw BoardException("Given rule string is not valid");
                }
                memcpy(buffer_board, board, rows * columns);
                if(rule_string != rule_string_) { // && isValidRuleString(rule_string_)
                    rule_string = rule_string_;
                    birth_values = getBirthValues(rule_string);
                    survival_values = getSurvivalValues(rule_string);
                }
                for(int i = 0; i < rows; i++) {
                    for(int j = 0; j < columns; j++) {
                        std::string number_of_neighbors = std::to_string(countNeighborsMoore(j, i));
                        if(!(board[i * columns + j]) && birth_values.find(number_of_neighbors) != std::string::npos) {
                            // Dead -> Alive
                            board[i * columns + j] = true;
                        } else if(board[i * columns + j] && survival_values.find(number_of_neighbors) != std::string::npos) {
                            // Alive -> Alive
                            continue;
                        } else {
                            // Dead -> Dead or Alive -> Dead
                            board[i * columns + j] = false;
                        }
                    }
                }
            }

        private:
            bool * buffer_board; // Buffer of board to separate neighbor count and update
            bool * board;
            size_t rows;
            size_t columns;
            std::string rule_string;
            std::string birth_values;
            std::string survival_values;
            const int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
            const int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    };
}

#endif