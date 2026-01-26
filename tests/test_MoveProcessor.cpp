#include "MoveProcessor.hpp"
#include "GameState.hpp"
#include "MarkerPositions.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Initialise MoveProcessor object", "[move][init]"){

    size_t startingOuterCell = 4;
    MoveProcessor mp(startingOuterCell); 

    REQUIRE(mp.getCurrentOuterCell() == startingOuterCell);
    REQUIRE(mp.getMoveConstraint() == MoveConstraint::FORCED_OUTER_CELL);

}

TEST_CASE("Apply Player Move Test", "[move][apply]"){

    size_t outerCell = 4;

    MoveProcessor move(outerCell);
    GameState gs;
    MarkerPositions position;
    BoardMarker nought = BoardMarker::NOUGHT;
    BoardMarker cross = BoardMarker::CROSS;

    const MatchEvaluation& eval = gs.getMatchEvaluation();
        
    SECTION("Empty Board"){

        size_t innerCell = 0;

        move.applyPlayerMove(nought, position, gs, innerCell);
        
        REQUIRE(move.getCurrentOuterCell() == innerCell);
        REQUIRE(move.getMoveConstraint() == MoveConstraint::FORCED_OUTER_CELL);
    }

    SECTION("Position Taken")

}