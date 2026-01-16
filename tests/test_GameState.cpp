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



TEST_CASE("Line Win State Updates to BLOCK", "[state]"){

    GameState gs;
    const MatchEvaluation& eval = gs.getMatchEvaluation();
    const OuterLWS& olws = eval.outerLineWinStates;
    MarkerPositions positions;
    PosUpdate update;

    positions.updateMarkerAtPos(0, 0, BoardMarker::CROSS, update);
    gs.updateGameState(positions.getMarkerPositions()[0], 0, 0);

    REQUIRE(olws[0][0] == LineWinState::ALIVE);

    positions.updateMarkerAtPos(0, 1, BoardMarker::NOUGHT, update);
    gs.updateGameState(positions.getMarkerPositions()[0], 0, 1);

    REQUIRE(olws[0][0] == LineWinState::BLOCKED);

}

TEST_CASE("Draw (tie) in an outer cell", "[state]"){

    GameState gs;
    const MatchEvaluation& eval = gs.getMatchEvaluation();
    MarkerPositions positions;
    PosUpdate update;
    BoardMarker marker = BoardMarker::NONE;

    size_t outerCell = 0;

    for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

        if(i % 2 == 0){
            marker = BoardMarker::CROSS;
        } else {
            marker = BoardMarker::NOUGHT;
        }

        positions.updateMarkerAtPos(outerCell, i, marker, update);

        gs.updateGameState(positions.getMarkerPositions()[outerCell], outerCell, i);
    }

    const OuterMS& ms = eval.outerMatchStates;

    REQUIRE(ms[outerCell] == MatchState::DRAW);
}