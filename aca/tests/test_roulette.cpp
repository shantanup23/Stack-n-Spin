#include "catch.hpp"
#include "../Roulette.hpp"

TEST_CASE("Roulette colorOf and payouts", "[roulette]") {
    // Note: initialBalance parameter is not used in logic, just for constructor symmetry
    Roulette game("TestPlayer", 100.0);

    // Color logic
    REQUIRE(game.colorOf(3) == "red");
    REQUIRE(game.colorOf(4) == "black");
    REQUIRE(game.colorOf(0) == "green");

    // Number bet: correct number wins, others lose
    RouletteBet numberBet = {"number", 7, 10};
    REQUIRE(game.payoutForBet(numberBet, 7) == 350.0);    // Win (10*35)
    REQUIRE(game.payoutForBet(numberBet, 8) == -10.0);    // Lose

    // Red/black bets
    RouletteBet redBet   = {"red", -1, 5};
    RouletteBet blackBet = {"black", -1, 5};
    REQUIRE(game.payoutForBet(redBet, 21) == 5.0);        // 21 is red
    REQUIRE(game.payoutForBet(redBet, 4)  == -5.0);       // 4 is black
    REQUIRE(game.payoutForBet(blackBet, 4) == 5.0);       // 4 is black
    REQUIRE(game.payoutForBet(blackBet, 17) == 5.0);     // 17 is black

    // Even/odd bets
    RouletteBet evenBet = {"even", -1, 8};
    RouletteBet oddBet  = {"odd", -1, 10};
    REQUIRE(game.payoutForBet(evenBet, 8) == 8.0);        // 8 is even
    REQUIRE(game.payoutForBet(evenBet, 7) == -8.0);       // 7 is odd
    REQUIRE(game.payoutForBet(oddBet, 17) == 10.0);       // 17 is odd
    REQUIRE(game.payoutForBet(oddBet, 2) == -10.0);       // 2 is even

    // Low/high bets
    RouletteBet lowBet = {"low", -1, 7};
    RouletteBet highBet = {"high", -1, 12};
    REQUIRE(game.payoutForBet(lowBet, 10) == 7.0);        // 10 is low
    REQUIRE(game.payoutForBet(lowBet, 30) == -7.0);       // 30 is high
    REQUIRE(game.payoutForBet(highBet, 35) == 12.0);      // 35 is high
    REQUIRE(game.payoutForBet(highBet, 9) == -12.0);      // 9 is low
}