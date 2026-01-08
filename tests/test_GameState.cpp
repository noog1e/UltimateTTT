#include <catch2/catch_test_macros.hpp>
#include "WinConditions.hpp"
#include "MarkerPositions.hpp"
#include "GameState.hpp"

TEST_CASE("Initialise Game State Object"){

    GameState gameState;

    const OuterStates& outerStates = gameState.getOuterStates();

    for(size_t i = 0; i < outerStates.size(); i++){

        REQUIRE(outerStates[i] == MatchState::ONGOING);
    }
}