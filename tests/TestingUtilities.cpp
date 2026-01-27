#include "TestingUtilities.hpp"
#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include "BoardLayout.hpp"
#include <cstddef>
#include <iostream>
#include <catch2/catch_test_macros.hpp>

void fillMarkerPositions(MarkerPositions& positions, BoardMarker marker){

    PosUpdate update;

    for(size_t i=0; i < BoardLayout::NUM_CELLS; i++){

        for(size_t j=0; j < BoardLayout::NUM_CELLS; j++){

            positions.updateMarkerAtPos(i, j, marker, update);
        }
    }
}

void requireAllPositionsAs(MarkerPositions& positions, BoardMarker marker){

    const OuterPos& outPos = positions.getMarkerPositions();

    for(size_t i=0; i < BoardLayout::NUM_CELLS; i++){

        const InnerPos& inPos = outPos[i];

        for(size_t j=0; j < BoardLayout::NUM_CELLS; j++){

            REQUIRE(inPos[j] == marker);
        }
    }

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

    PosUpdate update;

    positions.updateMarkerAtPos(outerCell, innerCell, marker, update);

    REQUIRE(update == PosUpdate::VALID);

    gs.updateGameState(positions.getMarkerPositions()[outerCell], outerCell, innerCell); //Starts crashing inside here
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
    setMarkerPosition(positions, gs, outerCell, 7, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 6, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 0, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 1, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 2, BoardMarker::NOUGHT);
}

void winRow2(MarkerPositions& positions, GameState& gs, size_t outerCell){
    setMarkerPosition(positions, gs, outerCell, 2, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 1, BoardMarker::NOUGHT);
    setMarkerPosition(positions, gs, outerCell, 3, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 4, BoardMarker::CROSS);
    setMarkerPosition(positions, gs, outerCell, 5, BoardMarker::CROSS);
    // Error after last set marker position
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

void tieMatch(MarkerPositions& positions, GameState& gs){
    
    winRow1(positions, gs, 0);
    winRow1(positions, gs, 1);
    winRow2(positions, gs, 2);
    winRow2(positions, gs, 3);
    winRow2(positions, gs, 4);
    winRow1(positions, gs, 5);
    winRow1(positions, gs, 6);
    winRow1(positions, gs, 7);
    winRow2(positions, gs, 8);
}