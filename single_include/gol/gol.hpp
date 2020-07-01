#ifndef GOL_HPP
#define GOL_HPP

#include <algorithm>
#include <fstream>
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
            int countNeighborsMoore(int x, int y, bool copy_board_to_buffer = true) {
                if(copy_board_to_buffer) {
                    memcpy(buffer_board, board, rows * columns);
                }
                int number_of_neighbors = 0;
                for(int i = 0; i < 8; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if(wrap) {
                        nx = (nx + columns) % columns;
                        ny = (ny + rows) % rows;
                    } else {
                        if(nx < 0 || ny < 0) continue;
                        if(nx >= columns || ny >= rows) continue;
                    }                        
                    if(buffer_board[ny * columns + nx]) number_of_neighbors++;
                }
                return number_of_neighbors;
            }

            // Counts neighbors as a Von Neumann neighborhood. Four
            // neighbors are analysed for their state.
            int countNeighborsNeumann(int x, int y, bool copy_board_to_buffer = true) {
                if(copy_board_to_buffer) {
                    memcpy(buffer_board, board, rows * columns);
                }
                int number_of_neighbors = 0;
                for(int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if(wrap) {
                        nx = (nx + columns) % columns;
                        ny = (ny + rows) % rows;
                    } else {
                        if(nx < 0 || ny < 0) continue;
                        if(nx >= columns || ny >= rows) continue;
                    }                        
                    if(buffer_board[ny * columns + nx]) number_of_neighbors++;
                }
                return number_of_neighbors;
            }

            // Iterate to the next time step
            void nextStep() {
                memcpy(buffer_board, board, rows * columns);
                birth_values = getBirthValues(rule_string);
                survival_values = getSurvivalValues(rule_string);
                for(int i = 0; i < rows; i++) {
                    for(int j = 0; j < columns; j++) {
                        std::string number_of_neighbors;
                        if(neighborhood_type == "moore") {
                            number_of_neighbors = std::to_string(countNeighborsMoore(j, i, false)); // false argument to avoid recopying to buffer board
                        } else if(neighborhood_type == "neumann") {
                            number_of_neighbors = std::to_string(countNeighborsNeumann(j, i, false)); // false argument to avoid recopying to buffer board
                        }
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

            // Sets wrap to user defined bool
            void setWrap(bool wrap_) {
                wrap = wrap_;
            }

            // Returns wrap bool
            bool getWrap() {
                return wrap;
            }

            // Sets neighborhood type based on given string
            void setNeighborhoodType(std::string neighborhood_type_) {
                std::transform(neighborhood_type_.begin(), neighborhood_type_.end(), neighborhood_type_.begin(),
                    [](unsigned char c){ return std::tolower(c); });
                if(neighborhood_type_ == "moore") {
                    neighborhood_type = "moore";
                } else if(neighborhood_type_ == "neumann") {
                    neighborhood_type = "neumann";
                } else {
                    throw BoardException("Given neighborhood type is not valid"); 
                }
            }

            // Returns current neighborhood type as a string
            std::string getNeighborhoodType() {
                return neighborhood_type;
            }

            // Set values of board from given file
            // File should follow proper board file format
            void setFromFile(std::string file_path) {
                std::fstream file;
                std::string line;
                int line_number = 0;
                int current_row = 0;
                file.open(file_path.c_str(), std::ios::in);
                if(!file) {
                    throw BoardException("Given file is not valid");
                }
                while(std::getline(file, line)) {
                    std::string line_content = ""; // Holds line without comments
                    for(int i = 0; i < line.length(); i++) {
                        if(line_number == 0 || line_number == 1) {
                            if(number_characters.find(line[i]) != std::string::npos) {
                                line_content.push_back(line[i]);
                            } else {
                                break;
                            }
                        } else {
                            if(live_cell_characters.find(line[i]) != std::string::npos || dead_cell_characters.find(line[i]) != std::string::npos) {
                                line_content.push_back(line[i]);
                            } else {
                                break;
                            }
                        }
                    }
                    if(line_number < 2) {
                        if (
                            (line_content.empty()) || 
                            (line_number == 0 && std::stoi(line_content) != rows) || 
                            (line_number == 1 && std::stoi(line_content) != columns)) {
                            throw BoardException("Given dimensions from file do not match board dimensions");
                        }
                    } else if(line_number >= 2 && !line_content.empty()) {
                        current_row = line_number - 2;
                        if(line_content.length() != columns || current_row >= rows) {
                            throw BoardException("Given board from file does not match specified dimensions");
                        } else {
                            for(int i = 0; i < line_content.length(); i++) {
                                if(dead_cell_characters.find(line[i]) != std::string::npos) {
                                    board[current_row * columns + i] = false;
                                } else if(live_cell_characters.find(line[i]) != std::string::npos) {
                                    board[current_row * columns + i] = true;
                                } 
                            }
                        }
                    }
                    line_number++;
                }
            }

            // Set values of board from given RLE file
            // File should follow proper RLE file format
            void setFromRLEFile(std::string file_path) {
                std::fstream file;
                std::string line;
                std::string board_string;     // Composite of the lines that represent the board
                int line_number = 0;
                bool reading_number = false;  // Represents if <run_count> number is currently being recorded
                std::string current_number;   // Current <run_count> number being read
                int current_row = 0;
                int current_column = 0;
                file.open(file_path.c_str(), std::ios::in);
                if(!file) {
                    throw BoardException("Given file is not valid");
                }
                while(std::getline(file, line)) {
                    line.erase(remove(line.begin(),line.end(),' '),line.end()); // Remove whitespace
                    std::transform(line.begin(), line.end(), line.begin(),
                        [](unsigned char c){ return std::tolower(c); }); // Transform to lower case
                    if(line[0] != '#') {
                        if(line_number == 0) {
                            bool reading_x = false;     // Represents if currently reading x property
                            bool reading_y = false;     // Represents if currently reading y property
                            bool reading_rule = false;  // Represents if currently reading rule property
                            std::string x;              // Holds x property
                            std::string y;              // Holds y property
                            std::string rule;           // Holds rule string
                            for(int i = 0; i < line.length(); i++) {
                                if(line[i] == 'x') {
                                    reading_x = true;
                                    reading_y = false;
                                    reading_rule = false;
                                } else if(line[i] == 'y') {
                                    reading_x = false;
                                    reading_y = true;
                                    reading_rule = false;
                                } else if(line[i] == 'r') {
                                    reading_x = false;
                                    reading_y = false;
                                    reading_rule = true;
                                }
                                if(reading_x && number_characters.find(line[i]) != std::string::npos) {
                                    x.push_back(line[i]);
                                } else if(reading_y && number_characters.find(line[i]) != std::string::npos) {
                                    y.push_back(line[i]);
                                } else if(reading_rule && valid_rule_string_characters.find(line[i]) != std::string::npos) {
                                    rule.push_back(line[i]);
                                }
                            }
                            if (
                                (x.empty() || y.empty()) ||
                                (std::stoi(x) != columns) || 
                                (std::stoi(y) != rows)) {
                                throw BoardException("Given dimensions from file do not match board dimensions");
                            } else if(!isValidRuleString(rule)) {
                                throw BoardException("Given rule string from file is not valid");
                            }
                        } else {
                            board_string += line;
                        }
                        line_number++;
                    }
                }
                for(int i = 0; i < rows * columns; i++) {
                    board[i] = false; // Naively assume all values are false
                }
                for(int i = 0; i < board_string.length(); i++) {
                    if(board_string[i] == '$') {
                        if(reading_number) {
                            // Skip multiple lines
                            current_row += std::stoi(current_number);
                        } else {
                            current_row++;
                        }
                        current_column = 0;
                        reading_number = false;
                        current_number = "";
                        if(current_row >= rows) {
                            throw BoardException("Given board from file does not match specified dimensions");
                        }
                    } else if(number_characters.find(board_string[i]) != std::string::npos) {
                        reading_number = true;
                        current_number.push_back(board_string[i]);
                    } else if(board_string[i] != '!') { // Exception: '!'. This character concludes the board
                        bool cell_state;
                        if(board_string[i] == 'b') { // Dead cell
                            cell_state = false;
                        } else { // Alive cell
                            //  RLE readers that cannot handle more than two states 
                            // should treat all letters other than b (and perhaps B) 
                            // as equivalent to o. 
                            cell_state = true;
                        }
                        if(reading_number) {
                            std::fill(
                                &board[current_row * columns + current_column], 
                                &board[current_row * columns + current_column] + std::stoi(current_number),
                                cell_state
                            );
                            current_column += std::stoi(current_number);
                        } else {
                            board[current_row * columns + current_column] = cell_state;
                            current_column++;
                        }
                        reading_number = false;
                        current_number = "";
                    } else {
                        break;
                    }
                }
            }

            // Returns the number of true elements on the board
            int getLiveCount() {
                int live_count = 0;
                for(int i = 0; i < rows * columns; i++) {
                    if(board[i] == true) {
                        live_count++;
                    }
                }
                return live_count;
            }

            // Returns the number of false elements on the board
            int getDeadCount() {
                int dead_count = 0;
                for(int i = 0; i < rows * columns; i++) {
                    if(board[i] == false) {
                        dead_count++;
                    }
                }
                return dead_count;
            }

            // Sets the rule string from given string in B/S notation
            // Includes validation
            void setRuleString(std::string rule_string_) {
                if(!isValidRuleString(rule_string)) {
                    throw BoardException("Given rule string is not valid");
                }
                rule_string = rule_string_;
            }

            // Returns current rule string
            std::string getRuleString() {
                return rule_string;
            }

        private:
            bool * buffer_board; // Buffer of board to separate neighbor count and update
            bool * board;
            bool wrap = true; // Represents if neighbor counting wraps around board or not
            size_t rows;
            size_t columns;
            std::string rule_string = "B3/S23";
            std::string birth_values;
            std::string survival_values;
            std::string neighborhood_type = "moore";
            std::string number_characters = "1234567890";
            std::string dead_cell_characters = ".-0";
            std::string live_cell_characters = "xX1oO";
            std::string valid_rule_string_characters = "b/s123456789";
            const int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
            const int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    };
}

#endif