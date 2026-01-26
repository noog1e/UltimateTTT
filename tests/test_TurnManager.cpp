#include "TurnManager.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Initialise TurnManager object", "[turn][init]"){

    size_t startingPlayer = 0;
    size_t numPlayers = 2;

    TurnManager tm(startingPlayer, numPlayers);

    REQUIRE(tm.currentPlayer() == startingPlayer);
    REQUIRE(tm.getPlayerCount() == numPlayers);
}

TEST_CASE("Next player test", "[turn][next]"){
    
    size_t startingPlayer = 0;
    size_t numPlayers = 2;

    TurnManager tm(startingPlayer, numPlayers);

    TurnOutcome outcome = TurnOutcome::NORMAL;
    tm.nextPlayer(outcome);

    size_t nextPlayer = 1;
    REQUIRE(tm.currentPlayer() == nextPlayer);
}

TEST_CASE("Alter player count", "[turn][count]"){
    
    size_t startingPlayer = 0;
    size_t numPlayers = 2;

    TurnManager tm(startingPlayer, numPlayers);

    numPlayers = 3;
    tm.setPlayerCount(numPlayers);

    REQUIRE(tm.getPlayerCount() == numPlayers);

}