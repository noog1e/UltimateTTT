#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <random>
#include <algorithm>

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

    std::cout << "\n";

    for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

        std::cout << markerToChar(inner[i]); 
    }
}

void setMarkerPosition(MarkerPositions& positions, GameState& gs, size_t outerCell, size_t innerCell, BoardMarker marker){

    REQUIRE(gs.getMatchEvaluation().overall.matchOutcome == MatchOutcome::ONGOING);

    PosUpdate update;

    positions.updateMarkerAtPos(outerCell, innerCell, marker, update);

    REQUIRE(update == PosUpdate::VALID);

    gs.updateGameState(positions.getMarkerPositions()[outerCell], outerCell, innerCell);
}

void tieMatch(MarkerPositions& positions, GameState& gs, size_t outerCell){
    setMarkerPosition(positions, gs, outerCell, 0, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 1, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 2, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 3, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 4, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 5, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 6, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 7, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 8, BoardMarker::NOUGHT);
}

void winRow1(MarkerPositions& positions, GameState& gs, size_t outerCell){
    setMarkerPosition(positions, gs, outerCell, 7, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 6, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 0, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 1, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 2, BoardMarker::CROSS);
}

void winRow2(MarkerPositions& positions, GameState& gs, size_t outerCell){
    setMarkerPosition(positions, gs, outerCell, 2, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 1, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 3, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 4, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 5, BoardMarker::CROSS);
}

void winRow3(MarkerPositions& positions, GameState& gs, size_t outerCell){
    setMarkerPosition(positions, gs, outerCell, 3, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 5, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 6, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 7, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 8, BoardMarker::CROSS);
}

void winCol1(MarkerPositions& positions, GameState& gs, size_t outerCell){
    setMarkerPosition(positions, gs, outerCell, 2, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 1, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 0, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 3, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 6, BoardMarker::CROSS);
}

void winCol2(MarkerPositions& positions, GameState& gs, size_t outerCell){
    setMarkerPosition(positions, gs, outerCell, 2, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 8, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 1, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 4, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 7, BoardMarker::CROSS);
}

void winCol3(MarkerPositions& positions, GameState& gs, size_t outerCell){
    setMarkerPosition(positions, gs, outerCell, 4, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 1, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 2, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 5, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 8, BoardMarker::CROSS);
}

void winDiag1(MarkerPositions& positions, GameState& gs, size_t outerCell){
    setMarkerPosition(positions, gs, outerCell, 2, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 1, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 0, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 4, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 8, BoardMarker::CROSS);
}

void winDiag2(MarkerPositions& positions, GameState& gs, size_t outerCell){
    setMarkerPosition(positions, gs, outerCell, 7, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 3, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 2, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 4, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 6, BoardMarker::CROSS);
}

TEST_CASE("Outer Cell Match Outcome Tests", "[state][outcome]"){

    GameState gs;
    MarkerPositions positions;
    size_t outerCell = 0;

    const MatchEvaluation& eval = gs.getMatchEvaluation();
    const OuterMES& outer = eval.outer;
    

    SECTION("Draw (tie)"){
        
        tieMatch(positions, gs, outerCell);

        REQUIRE(outer[outerCell].matchOutcome == MatchOutcome::DRAW);
    }

    SECTION("WIN Row 1"){
        
        winRow1(positions, gs, outerCell);

        REQUIRE(outer[outerCell].matchOutcome == MatchOutcome::CROSS_WON);
    }

    SECTION("WIN Row 2"){
        
        winRow2(positions, gs, outerCell);

        REQUIRE(outer[outerCell].matchOutcome == MatchOutcome::CROSS_WON);
    }

    SECTION("WIN Row 3"){
        
        winRow3(positions, gs, outerCell);

        REQUIRE(outer[outerCell].matchOutcome == MatchOutcome::CROSS_WON);
    }

    SECTION("WIN Col 1"){
        
        winCol1(positions, gs, outerCell);

        REQUIRE(outer[outerCell].matchOutcome == MatchOutcome::CROSS_WON);
    }

    SECTION("WIN Col 2"){
        
        winCol2(positions, gs, outerCell);

        REQUIRE(outer[outerCell].matchOutcome == MatchOutcome::CROSS_WON);
    }

    SECTION("WIN Col 3"){
        
        winCol3(positions, gs, outerCell);

        REQUIRE(outer[outerCell].matchOutcome == MatchOutcome::CROSS_WON);
    }

    SECTION("WIN Diag 1"){
        
        winDiag1(positions, gs, outerCell);

        REQUIRE(outer[outerCell].matchOutcome == MatchOutcome::CROSS_WON);
    }

    SECTION("WIN Diag 2"){
        
        winDiag2(positions, gs, outerCell);

        REQUIRE(outer[outerCell].matchOutcome == MatchOutcome::CROSS_WON);
    }

}

TEST_CASE("Overall Match Outcome Tests", "[state][outcome]"){

}