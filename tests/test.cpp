#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../single_include/gol/gol.hpp"

TEST_CASE("Game of Life", "[gol]") {

    REQUIRE(gol::getBirthValues("B4678/S35678")    == "4678" );
    REQUIRE(gol::getSurvivalValues("B4678/S35678") == "35678");
}