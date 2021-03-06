#include <catch2/catch.hpp>

#include "../single_include/gol/gol.hpp"

void setBoardAsFalse(gol::Board &board) {
    for(int i = 0; i < board.height(); i++) {
        for(int j = 0; j < board.width(); j++) {
            board[i][j] = false;
        }
    }
}

TEST_CASE("Game of Life", "[gol]") {

    SECTION("Rule String Validation", "[rule_string_validation]") {
        REQUIRE(gol::getBirthValues("B4678/S35678") == "4678");
        REQUIRE(gol::getSurvivalValues("B4678/S35678") == "35678");
        REQUIRE(gol::isValidRuleString("B123/S456789") == true);
        REQUIRE(gol::isValidRuleString("bb123//ss123") == false);
        REQUIRE(gol::isValidRuleString("B123/S456789%") == false);
    }

    SECTION("Board", "[board]") {
        gol::Board board(10, 20);
        REQUIRE(board.height() == 10);
        REQUIRE(board.width() == 20);
        board[0][0] = true;
        board[0][1] = false;
        REQUIRE(board[0][0] == true);
        REQUIRE(board[0][1] == false);
        try {
            board[11][20] = true;
        } catch(gol::BoardException& e) {
            REQUIRE(std::string(e.what()) == "Board index out of bound");
        }
    }

    SECTION("Wrapping State", "[wrap]") {
        gol::Board board(10, 20);
        REQUIRE(board.getWrap() == true); // true is default value
        board.setWrap(false);
        REQUIRE(board.getWrap() == false);
    }

    SECTION("Rule String Set and Get", "[rule_string]") {
        gol::Board board(10, 20);
        REQUIRE(board.getRuleString() == "B3/S23"); // "B3/S23" is default value
        board.setRuleString("B3/S1234");
        REQUIRE(board.getRuleString() == "B3/S1234");
        try {
            board.setRuleString("this_rule_string_does_not_exist");
        } catch(gol::BoardException& e) {
            REQUIRE(std::string(e.what()) == "Given rule string is not valid");
        }
    }

    SECTION("Neighborhood Type", "[neighborhood_type]") {
        gol::Board board(10, 20);
        REQUIRE(board.getNeighborhoodType() == "moore"); // "moore" is default value
        board.setNeighborhoodType("NeUmaNn");
        REQUIRE(board.getNeighborhoodType() == "neumann");
        try {
            board.setNeighborhoodType("not_a_valid_neighborhood_type");
        } catch(gol::BoardException& e) {
            REQUIRE(std::string(e.what()) == "Given neighborhood type is not valid");
        }
    }

    SECTION("Neighborhood Count", "[neighborhood_count]") {
        SECTION("Normal Neighborhood Count") {
            gol::Board board (10, 10);
            bool boardTemplate[10][10] = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
                {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
                {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            };
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    board[i][j] = boardTemplate;
                }
            }
            REQUIRE(board.countNeighborsMoore(4, 4) == 8);
            REQUIRE(board.countNeighborsNeumann(4, 4) == 4);
        }
        SECTION("No Wrapping Neighborhood Count") {
            gol::Board board (10, 10);
            board.setWrap(false);
            bool boardTemplate[10][10] = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            };
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    board[i][j] = boardTemplate;
                }
            }
            REQUIRE(board.countNeighborsMoore(4, 9) == 5);
            REQUIRE(board.countNeighborsNeumann(4, 9) == 3);
        }
        SECTION("Wrapping Neighborhood Count") {
            gol::Board board (10, 10);
            board.setWrap(true);
            bool boardTemplate[10][10] = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            };
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    board[i][j] = boardTemplate;
                }
            }
            REQUIRE(board.countNeighborsMoore(4, 9) == 8);
            REQUIRE(board.countNeighborsNeumann(4, 9) == 4);
        }

    }

    SECTION("Game of Life Simulations", "[simulations]") {
        SECTION("Beacon Oscillator") {
            gol::Board board(10, 10);
            setBoardAsFalse(board);
            board[2][2] = true;
            board[2][3] = true;
            board[3][2] = true;
            board[4][5] = true;
            board[5][4] = true;
            board[5][5] = true;
            board.nextStep();
            bool expectedBoard[10][10] = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            };
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == expectedBoard[i][j]);
                }
            }
        }
        SECTION("Blinker Oscillator") {
            gol::Board board(10, 10);
            setBoardAsFalse(board);
            board[2][2] = true;
            board[2][3] = true;
            board[2][4] = true;
            board.nextStep();
            bool expectedBoard[10][10] = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            };
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == expectedBoard[i][j]);
                }
            }
        }
        SECTION("Toad Oscillator") {
            gol::Board board(10, 10);
            setBoardAsFalse(board);
            board[2][3] = true;
            board[2][4] = true;
            board[2][5] = true;
            board[3][2] = true;
            board[3][3] = true;
            board[3][4] = true;
            board.nextStep();
            bool expectedBoard[10][10] = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                {0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
                {0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
                {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            };
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == expectedBoard[i][j]);
                }
            }
        }
    }

    SECTION("Set Board From File", "[set_board_from_file]") {
        SECTION("Pass") {
            gol::Board board(5, 9);
            board.setFromFile("tests/board_files/pass.txt");
            bool expectedBoard[5][9] = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 1, 1, 1, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
            };
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == expectedBoard[i][j]);
                }
            }
        }
        SECTION("Fail0") {
            gol::Board board(5, 9);
            try {
                board.setFromFile("this_file_does_not_exist.txt");
            } catch(gol::BoardException& e) {
                REQUIRE(std::string(e.what()) == "Given file is not valid");
            }
        }
        SECTION("Fail1") {
            gol::Board board(5, 9);
            try {
                board.setFromFile("tests/board_files/fail1.txt");
            } catch(gol::BoardException& e) {
                REQUIRE(std::string(e.what()) == "Given dimensions from file do not match board dimensions");
            }
        }
        SECTION("Fail2") {
            gol::Board board(5, 9);
            try {
                board.setFromFile("tests/board_files/fail2.txt");
            } catch(gol::BoardException& e) {
                REQUIRE(std::string(e.what()) == "Given board from file does not match specified dimensions");
            }
        }
        SECTION("Fail3") {
            gol::Board board(5, 9);
            try {
                board.setFromFile("tests/board_files/fail3.txt");
            } catch(gol::BoardException& e) {
                REQUIRE(std::string(e.what()) == "Given board from file does not match specified dimensions");
            }
        }
        SECTION("Fail4") {
            gol::Board board(5, 9);
            try {
                board.setFromFile("tests/board_files/fail4.txt");
            } catch(gol::BoardException& e) {
                REQUIRE(std::string(e.what()) == "Given dimensions from file do not match board dimensions");
            }
        }
        SECTION("Fail5") {
            gol::Board board(5, 9);
            try {
                board.setFromFile("tests/board_files/fail5.txt");
            } catch(gol::BoardException& e) {
                REQUIRE(std::string(e.what()) == "Given board from file does not match specified dimensions");
            }
        }
    }

    SECTION("Set Board From RLE File", "[set_board_from_rle_file]") {
        SECTION("Dragon RLE") {
            gol::Board expectedBoard(18, 29);
            expectedBoard.setFromFile("tests/rle_files/dragon.txt");
            gol::Board board(18, 29);
            board.setFromRLEFile("tests/rle_files/dragon.rle");
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == expectedBoard[i][j]);
                }
            }
        }
        SECTION("Blinker RLE") {
            gol::Board expectedBoard(1, 3);
            expectedBoard.setFromFile("tests/rle_files/blinker.txt");
            gol::Board board(1, 3);
            board.setFromRLEFile("tests/rle_files/blinker.rle");
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == expectedBoard[i][j]);
                }
            }
        }
        SECTION("60P312 RLE") {
            gol::Board expectedBoard(42, 42);
            expectedBoard.setFromFile("tests/rle_files/60P312.txt");
            gol::Board board(42, 42);
            board.setFromRLEFile("tests/rle_files/60P312.rle");
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == expectedBoard[i][j]);
                }
            }
        }
        SECTION("Fail1 RLE") {
            gol::Board board(42, 42);
            try {
                board.setFromRLEFile("tests/rle_files/fail1.rle");
            } catch(gol::BoardException& e) {
                REQUIRE(std::string(e.what()) == "Given dimensions from file do not match board dimensions");
            }
        }
        SECTION("Fail2 RLE") {
            gol::Board board(42, 42);
            try {
                board.setFromRLEFile("tests/rle_files/fail2.rle");
            } catch(gol::BoardException& e) {
                REQUIRE(std::string(e.what()) == "Given rule string from file is not valid");
            }
        }
        SECTION("Fail3 RLE") {
            gol::Board board(42, 42);
            try {
                board.setFromRLEFile("tests/rle_files/fail3.rle");
            } catch(gol::BoardException& e) {
                REQUIRE(std::string(e.what()) == "Given board from file does not match specified dimensions");
            }
        }
    }

    SECTION("Saving board as file", "[save_board_as_file]") {
        SECTION("60P312") {
            gol::Board board(42, 42);
            board.setFromFile("tests/rle_files/60P312.txt");
            board.saveAsFile("tests/rle_files/60P312_written.txt");
            gol::Board check_board(42, 42);
            check_board.setFromFile("tests/rle_files/60P312_written.txt");
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == check_board[i][j]);
                }
            }
        }
        SECTION("Blinker") {
            gol::Board board(1, 3);
            board.setFromFile("tests/rle_files/blinker.txt");
            board.saveAsFile("tests/rle_files/blinker_written.txt");
            gol::Board check_board(1, 3);
            check_board.setFromFile("tests/rle_files/blinker_written.txt");
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == check_board[i][j]);
                }
            }
        }
        SECTION("Dragon") {
            gol::Board board(18, 29);
            board.setFromFile("tests/rle_files/dragon.txt");
            board.saveAsFile("tests/rle_files/dragon_written.txt");
            gol::Board check_board(18, 29);
            check_board.setFromFile("tests/rle_files/dragon_written.txt");
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == check_board[i][j]);
                }
            }
        }
    }

    SECTION("Saving board as RLE file", "[save_board_as_rle_file]") {
        SECTION("60P312 RLE") {
            gol::Board board(42, 42);
            board.setFromRLEFile("tests/rle_files/60P312.rle");
            board.saveAsRLEFile("tests/rle_files/60P312_written.rle");
            gol::Board check_board(42, 42);
            check_board.setFromRLEFile("tests/rle_files/60P312_written.rle");
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == check_board[i][j]);
                }
            }
        }
        SECTION("Blinker RLE") {
            gol::Board board(1, 3);
            board.setFromRLEFile("tests/rle_files/blinker.rle");
            board.saveAsRLEFile("tests/rle_files/blinker_written.rle");
            gol::Board check_board(1, 3);
            check_board.setFromRLEFile("tests/rle_files/blinker_written.rle");
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == check_board[i][j]);
                }
            }
        }
        SECTION("Dragon RLE") {
            gol::Board board(18, 29);
            board.setFromRLEFile("tests/rle_files/dragon.rle");
            board.saveAsRLEFile("tests/rle_files/dragon_written.rle");
            gol::Board check_board(18, 29);
            check_board.setFromRLEFile("tests/rle_files/dragon_written.rle");
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    REQUIRE(board[i][j] == check_board[i][j]);
                }
            }
        }
    }

    SECTION("Get Live and Dead Count", "[live_and_dead_count]") {
        gol::Board board(10, 10);
        bool boardTemplate[10][10] = {
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        };
        for(int i = 0; i < board.height(); i++) {
            for(int j = 0; j < board.width(); j++) {
                board[i][j] = boardTemplate[i][j];
            }
        }
        REQUIRE(board.getLiveCount() == 10);
        REQUIRE(board.getDeadCount() == 90);
    }
}