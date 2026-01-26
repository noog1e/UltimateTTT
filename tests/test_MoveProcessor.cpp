#include "MoveProcessor.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Initialise MoveProcessor object", "[move][init]"){

    MoveProcessor mp; 

    REQUIRE(mp.getCurrentOuterCell() == 0);
    REQUIRE(mp.getMoveConstraint() == MoveConstraint::FORCED_OUTER_CELL);
}