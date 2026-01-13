#include <catch2/catch_test_macros.hpp>
#include "MarkerPositions.hpp"
#include "GameState.hpp"

TEST_CASE("Initialise Game State Object", "[state][init]"){

    GameState gs;

    SECTION("Overall Match State is ONGOING"){

        REQUIRE(gs.getOverallMatchState() == MatchState::ONGOING);
    }

    SECTION("All Outer Match States are ONGOING"){
        
        const OuterMS& outerMS = gs.getOuterMatchStates();

        for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

            REQUIRE(outerMS[i] == MatchState::ONGOING);
        }
    }

    SECTION("All Outer Line Win States are ALIVE"){

        const OuterLWS& outerLWS = gs.getOuterLineWinStates();

        for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){
        
            for(size_t j = 0; j < NUM_CELL_COMBOS; j++){
                REQUIRE(outerLWS[i][j] == LineWinState::ALIVE);
            }
        }
    }
}