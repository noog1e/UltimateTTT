#pragma once

#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include <cstddef>

void fillMarkerPositions(MarkerPositions& positions, BoardMarker marker);
void requireAllPositionsAs(MarkerPositions& positions, BoardMarker marker);
char markerToChar(BoardMarker marker);
void printInnerPos(const InnerPos& inner);
void setMarkerPosition(
    MarkerPositions& positions, 
    GameState& gs, 
    size_t outerCell, 
    size_t innerCell, 
    BoardMarker marker
);
void tieMatch(MarkerPositions& positions, GameState& gs, size_t outerCell);
void winRow1(MarkerPositions& positions, GameState& gs, size_t outerCell);
void winRow2(MarkerPositions& positions, GameState& gs, size_t outerCell);
void winRow3(MarkerPositions& positions, GameState& gs, size_t outerCell);
void winCol1(MarkerPositions& positions, GameState& gs, size_t outerCell);
void winCol2(MarkerPositions& positions, GameState& gs, size_t outerCell);
void winCol3(MarkerPositions& positions, GameState& gs, size_t outerCell);
void winDiag1(MarkerPositions& positions, GameState& gs, size_t outerCell);
void winDiag2(MarkerPositions& positions, GameState& gs, size_t outerCell);
void tieMatch(MarkerPositions& positions, GameState& gs);