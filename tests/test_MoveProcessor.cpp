#include "MoveProcessor.hpp"
#include "GameState.hpp"
#include "MarkerPositions.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Initialise MoveProcessor object", "[move][init]"){

    size_t startingOuterCell = 4;
    MoveProcessor mp(startingOuterCell); 

    REQUIRE(mp.getCurrentOuterCell() == 0);
    REQUIRE(mp.getMoveConstraint() == MoveConstraint::FORCED_OUTER_CELL);

    
    mp.setCurrentOuterCell()
}

TEST_CASE("Functionality tests"){

    MoveProcessor move;
    GameState gs;
    MarkerPositions position;
    PosUpdate update;

    const MatchEvaluation& eval = gs.getMatchEvaluation();
        


}