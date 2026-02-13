#include "TestingUtilities.hpp"
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

TEST_CASE("Inner Cell move correlates with Occupied Outer Cell", "[move][occupied]"){
    
    size_t outerCell = 0;

    GameState gs;
    MarkerPositions positions;

    winRow1(positions, gs, outerCell);

    outerCell = 1;
    MoveProcessor move(outerCell);

    //This shows if an outer cell has been captured or is in a tie state, 
    //the current outer cell in MoveProcessor remains the same value.
    //This is a key indicator combined with the MoveConstraint that the
    //outer cell is occupied, and the next player gets a free move.
    REQUIRE(move.getCurrentOuterCell() == outerCell);
    REQUIRE(move.getMoveConstraint() == MoveConstraint::ANY);

    const MatchEvaluation& eval = gs.getMatchEvaluation();
    const OuterMES& outerMES = eval.outer;

    SECTION("Moving to any unoccupied position as ANY state is triggered"){

        size_t newOuterCell = 2;
        move.setCurrentOuterCell(newOuterCell, outerMES);

        REQUIRE(move.getCurrentOuterCell() == newOuterCell);
        REQUIRE(move.getMoveConstraint() == MoveConstraint::FORCED_OUTER_CELL);
    }

    SECTION("Moving to any occupied position as ANY state is triggered"){

        size_t newOuterCell = 0;
        move.setCurrentOuterCell(newOuterCell, outerMES);

        REQUIRE(move.getCurrentOuterCell() == outerCell);
        REQUIRE(move.getMoveConstraint() == MoveConstraint::ANY);
    }
    
}