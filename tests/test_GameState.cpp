#include "TestingUtilities.hpp"
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


TEST_CASE("Line Win State Updates to BLOCK", "[state][block]"){

    GameState gs;
    const MatchEvaluation& eval = gs.getMatchEvaluation();
    const OuterMES& outer = eval.outer;
    MarkerPositions positions;
    PosUpdate update;

    size_t outerCell = 0;
    size_t innerCell = 0;

    positions.updateMarkerAtPos(outerCell, innerCell, BoardMarker::CROSS, update);
    REQUIRE(update == PosUpdate::VALID);
    gs.updateGameState(positions.getMarkerPositions()[outerCell], outerCell, innerCell);

    REQUIRE(outer[outerCell].lineWinStates[0] == LineWinState::ALIVE);

    innerCell = 1;

    positions.updateMarkerAtPos(outerCell, innerCell, BoardMarker::NOUGHT, update);
    REQUIRE(update == PosUpdate::VALID);
    gs.updateGameState(positions.getMarkerPositions()[outerCell], outerCell, innerCell);

    innerCell = 2;

    positions.updateMarkerAtPos(outerCell, innerCell, BoardMarker::NOUGHT, update);
    REQUIRE(update == PosUpdate::VALID);
    gs.updateGameState(positions.getMarkerPositions()[outerCell], outerCell, innerCell);

    REQUIRE(outer[outerCell].lineWinStates[0] == LineWinState::BLOCKED);
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

        REQUIRE(outer[outerCell].matchOutcome == MatchOutcome::NOUGHT_WON);
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

TEST_CASE("Overall Match Outcome Tests", "[state][outcome][overall]"){

    GameState gs;
    MarkerPositions positions;
    const MatchEvaluation& eval = gs.getMatchEvaluation();
    const MatchEvaluationState& overall = eval.overall;

    SECTION("Tie from individual matches being a draw"){
        
        for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

            tieMatch(positions, gs, i);

        }

        REQUIRE(overall.matchOutcome == MatchOutcome::DRAW);
    }

    SECTION("Natural tie from CROSS NOUGHT take over"){
        tieMatch(positions, gs);

        REQUIRE(overall.matchOutcome == MatchOutcome::DRAW);
    }

    SECTION("Game Win"){
        winRow1(positions, gs, 0);
        winRow1(positions, gs, 1);
        winRow1(positions, gs, 2);
        
        REQUIRE(overall.matchOutcome == MatchOutcome::NOUGHT_WON);
    }

}