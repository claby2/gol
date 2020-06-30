#define CATCH_CONFIG_MAIN
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

    SECTION("Rule String", "[rule_string]") {
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
        try {
            board.nextStep("not_a_valid_rule_string");
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

    SECTION("Wrapping State", "[wrap]") {
        gol::Board board(10, 20);
        REQUIRE(board.getWrap() == true); // true is default value
        board.setWrap(false);
        REQUIRE(board.getWrap() == false);
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
            board.nextStep("B3/S23");
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
            board.nextStep("B3/S23");
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
            board.nextStep("B3/S23");
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

}