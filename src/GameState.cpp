#include "WinConditions.hpp"
#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include <cstddef>

GameState::GameState(){
    outerStates.fill(MatchState::ONGOING);
}

void GameState::updateOuterState(const OuterPos& outerPos, size_t outerCell){

    const InnerPos& innerPos = outerPos[outerCell];

    MatchState cellState = MatchState::ONGOING;

    cellState = checkDraw(innerPos);

    if(cellState != MatchState::DRAW){

        cellState = checkWinState(innerPos);

    }

    outerStates[outerCell] = cellState;
}

void GameState::updateMatchState(){

    MatchState checkState = MatchState::ONGOING;

    checkState = checkDraw();

    if(checkState != MatchState::DRAW){

        checkState = checkWinState();

    }

    matchState = checkState;
}

const OuterStates& GameState::getOuterStates() const{
    return outerStates;
}

MatchState GameState::getMatchState() const{
    return matchState;
}

bool GameState::matchPosition(BoardMarker m1, BoardMarker m2) const{

    if(m1 == BoardMarker::NONE || m2 == BoardMarker::NONE) return false;

    return m1 == m2;
}

bool GameState::matchPosition(MatchState s1, MatchState s2) const{

    if(s1 == MatchState::ONGOING || s2 == MatchState::ONGOING) return false;

    return s1 == s2;
}

MatchState GameState::checkWinState(const InnerPos& inner) const{

    MatchState cellState = MatchState::ONGOING;

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
            cellState = assignOuterWinner(marker1);
        }
    }

    return cellState;
}

MatchState GameState::checkWinState() const{
    
    MatchState state1 = MatchState::ONGOING;
    MatchState state2 = MatchState::ONGOING;

    for(size_t i = 0; i < NUM_CELL_COMBOS; i++){
    
        int matchCount = 1;

        for(size_t j = 0; j < BoardLayout::CELLS_PER_AXIS - 1; j++){

            state1 = outerStates[WIN_CONDITIONS[i][j]];
            state2 = outerStates[WIN_CONDITIONS[i][j+1]];

            if(matchPosition(state1, state2)){
                matchCount++;
            }else{
                break;
            }
        }

        if(matchCount == BoardLayout::CELLS_PER_AXIS){
            return state1;
        }
    }

    return MatchState::ONGOING;
}

MatchState GameState::checkDraw(const InnerPos& inner) const{

    for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

        if(inner[i] == BoardMarker::NONE) return MatchState::ONGOING;
    }

    return MatchState::DRAW;
}

MatchState GameState::checkDraw() const{

    for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

        if(outerStates[i] == MatchState::ONGOING) return MatchState::ONGOING;
    }

    return MatchState::DRAW;

}

MatchState GameState::assignOuterWinner(BoardMarker marker) const{

    MatchState winner = MatchState::ONGOING;

    if(marker == BoardMarker::CROSS) winner = MatchState::CROSS_WON;
    if(marker == BoardMarker::NOUGHT) winner = MatchState::NOUGHT_WON;

    return winner;
}