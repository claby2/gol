#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../single_include/gol/gol.hpp"

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
    }

}