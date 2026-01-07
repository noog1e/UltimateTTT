#include "game.hpp"
#include "WinConditions.hpp"

GameState::GameState(const MarkerPositions& positions) : markerPositions(positions){
    state.fill(OuterCellState::ONGOING);
}

void GameState::checkInnerWinState(size_t outerCell){

    BoardMarker marker = BoardMarker::NONE;

    for(size_t i = 0; i < NUM_CELL_COMBOS; i++){
        
        for(size_t j = 0; j < BoardLayout::CELLS_PER_AXIS - 1; j++){

            
        }
    }
}

bool GameState::matchPosition(BoardMarker m1, BoardMarker m2){

    return m1 == m2 && m1 != BoardMarker::NONE && m2 != BoardMarker::NONE;
}