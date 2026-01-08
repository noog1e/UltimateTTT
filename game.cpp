#include "game.hpp"
#include "WinConditions.hpp"

GameState::GameState(const MarkerPositions& positions) : markerPositions(positions){
    state.fill(OuterCellState::ONGOING);
}

void GameState::checkInnerState(size_t outerCell){

    const InnerPos& inner = markerPositions.getMarkerPositions()[outerCell];

    OuterCellState cellState = OuterCellState::ONGOING;

    cellState = checkInnerDraw(inner);

    if(cellState != OuterCellState::DRAW){

        cellState = checkInnerWinState(inner);

    }

    state[outerCell] = cellState;
}

OuterCellState GameState::checkInnerWinState(const InnerPos& inner) const{

    OuterCellState cellState = OuterCellState::ONGOING;

    BoardMarker marker1 = BoardMarker::NONE;
    BoardMarker marker2 = BoardMarker::NONE;

    for(size_t i = 0; i < NUM_CELL_COMBOS; i++){
        
        int matchCount = 1;

        for(size_t j = 0; j < BoardLayout::CELLS_PER_AXIS - 1; j++){

            marker1 = inner[WIN_CONDITIONS[i][j]];
            marker2 = inner[WIN_CONDITIONS[i][j+1]];

            if(matchPosition(marker1, marker2)){
                matchCount++;
            }else{
                break;
            }
        }

        if(matchCount == BoardLayout::CELLS_PER_AXIS){
            cellState = assignWinner(marker1);
        }
    }

    return cellState;
}

bool GameState::matchPosition(BoardMarker m1, BoardMarker m2) const{

    return m1 == m2 && m1 != BoardMarker::NONE && m2 != BoardMarker::NONE;
}

OuterCellState GameState::assignWinner(BoardMarker marker) const{

    OuterCellState winner = OuterCellState::ONGOING;

    if(marker == BoardMarker::CROSS) winner = OuterCellState::CROSS_WON;
    if(marker == BoardMarker::NOUGHT) winner = OuterCellState::NOUGHT_WON;

    return winner;
}

OuterCellState GameState::checkInnerDraw(const InnerPos& inner) const{

    for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

        if(inner[i] == BoardMarker::NONE) return OuterCellState::DRAW;
    }

    return OuterCellState::ONGOING;
}