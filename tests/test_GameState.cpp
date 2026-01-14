#include <catch2/catch_test_macros.hpp>
#include "MarkerPositions.hpp"
#include "GameState.hpp"

TEST_CASE("Initialise Game State Object", "[state][init]"){

    GameState gs;
    const MatchEvaluation& eval = gs.getMatchEvaluation(); 

    SECTION("Overall Match State is ONGOING"){

        REQUIRE(eval.overallMatchState == MatchState::ONGOING);
    }

    SECTION("All Outer Match States are ONGOING"){
        
        const OuterMS& outerMS = eval.outerMatchStates;

        for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

            REQUIRE(outerMS[i] == MatchState::ONGOING);
        }
    }

    SECTION("All Overall Line Win States are ALIVE"){
        
        const LineWinStates& lws = eval.overallLineWinStates;
        
        for(size_t i = 0; i < NUM_CELL_COMBOS; i++){
            REQUIRE(lws[i] == LineWinState::ALIVE);
        }
    }

    SECTION("All Outer Line Win States are ALIVE"){

        const OuterLWS& outerLWS = eval.outerLineWinStates;

        for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){
        
            for(size_t j = 0; j < NUM_CELL_COMBOS; j++){
                REQUIRE(outerLWS[i][j] == LineWinState::ALIVE);
            }
        }
    }
}

TEST_CASE("Reset Game State object"){

}



TEST_CASE("Line Win State Updates to BLOCK"){

    GameState gs;
    const MatchEvaluation& eval = gs.getMatchEvaluation();
    MarkerPositions positions;

    

}