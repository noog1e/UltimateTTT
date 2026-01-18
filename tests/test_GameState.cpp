#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("Initialise Game State Object", "[state][init]"){

    GameState gs;
    const MatchEvaluation& eval = gs.getMatchEvaluation(); 

    const MatchEvaluationState& overall = eval.overall;
    const OuterMES& outer = eval.outer;

    SECTION("Overall Match State is ONGOING"){

        REQUIRE(overall.matchOutcome == MatchOutcome::ONGOING);
    }

    SECTION("All Outer Match States are ONGOING"){
        
        for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

            REQUIRE(outer[i].matchOutcome == MatchOutcome::ONGOING);
        }
    }

    SECTION("All Overall Line Win States are ALIVE"){
        
        const LineWinStates& lws = overall.lineWinStates;
        
        for(size_t i = 0; i < NUM_CELL_COMBOS; i++){
            REQUIRE(lws[i] == LineWinState::ALIVE);
        }
    }

    SECTION("All Outer Line Win States are ALIVE"){

        for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){
        
            const LineWinStates& lws = outer[i].lineWinStates;

            for(size_t j = 0; j < NUM_CELL_COMBOS; j++){
                REQUIRE(lws[j] == LineWinState::ALIVE);
            }
        }
    }
}

TEST_CASE("Reset Game State object"){

}



TEST_CASE("Line Win State Updates to BLOCK", "[state]"){

    GameState gs;
    const MatchEvaluation& eval = gs.getMatchEvaluation();
    const OuterMES& outer = eval.outer;
    MarkerPositions positions;
    PosUpdate update;

    positions.updateMarkerAtPos(0, 0, BoardMarker::CROSS, update);
    gs.updateGameState(positions.getMarkerPositions()[0], 0, 0);

    REQUIRE(outer[0].lineWinStates[0] == LineWinState::ALIVE);

    positions.updateMarkerAtPos(0, 1, BoardMarker::NOUGHT, update);
    gs.updateGameState(positions.getMarkerPositions()[0], 0, 1);

    REQUIRE(outer[0].lineWinStates[0] == LineWinState::BLOCKED);

}

char markerToChar(BoardMarker marker){

    if(marker == BoardMarker::CROSS) return 'x';
    if(marker == BoardMarker::NOUGHT) return 'o';

    return ' ';
}

void printInnerPos(const InnerPos& inner){

    for(size_t i = 0; i < BoardLayout::CELLS_PER_AXIS; i++){

        for(size_t j = 0; j < BoardLayout::CELLS_PER_AXIS; j++){
            
            std::cout << markerToChar(inner[i+j]);
        }

        std::cout << "\n";
    }
}

TEST_CASE("Draw (tie) in an outer cell", "[state][draw]"){

    GameState gs;
    const MatchEvaluation& eval = gs.getMatchEvaluation();
    const OuterMES& outer = eval.outer;
    MarkerPositions positions;
    PosUpdate update;
    BoardMarker marker = BoardMarker::NONE;

    size_t outerCell = 0;

    for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

        if(i % 2 == 0){
            marker = BoardMarker::NOUGHT;
        }else{
            marker = BoardMarker::CROSS;
        }

        positions.updateMarkerAtPos(outerCell, i, marker, update);

        REQUIRE(update == PosUpdate::VALID);

        gs.updateGameState(positions.getMarkerPositions()[outerCell], outerCell, i);

    }

    printInnerPos(positions.getMarkerPositions()[outerCell]);

    std::cout << "\nBlocked lines: " << outer[outerCell].blockedLines << "\n";

    REQUIRE(outer[outerCell].matchOutcome == MatchOutcome::NOUGHT_WON);

}