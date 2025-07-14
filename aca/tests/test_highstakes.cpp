
#include "catch.hpp"
#include "../Highstakes.hpp"

TEST_CASE("card value calculation","[Highstakes]"){
    Highstakes game("Test",100);
     
        
        REQUIRE(game.cardValue("A") == 14);
        REQUIRE(game.cardValue("8") == 8);
        REQUIRE(game.cardValue("K") == 13);
        REQUIRE(game.cardValue("Q") == 12);
        REQUIRE(game.cardValue("J") == 11);
        REQUIRE(game.cardValue("2") == 2);

    
}