#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include <cstddef>
#include <array>

GameState::GameState(){
    outerStates.fill(MatchState::ONGOING);
    
    for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){
        lineStates[i].fill(LineState::ALIVE);
    }
}

void GameState::updateOuterState(const OuterPos& outerPos, size_t outerCellUpdated, size_t innerCellUpdated){

    outerCellUpdated--;
    innerCellUpdated--;

    //BOUNDS CHECKING NEEDED

    const InnerPos& innerPos = outerPos[outerCellUpdated];

    MatchState cellState = MatchState::ONGOING;

    cellState = checkDrawState(innerPos);

    if(cellState != MatchState::DRAW){

        cellState = checkWinState(innerPos);

    }

    outerStates[outerCellUpdated] = cellState;
}

void GameState::updateMatchState(){

    MatchState checkState = MatchState::ONGOING;

    checkState = checkDrawState();

    if(checkState != MatchState::DRAW){

        checkState = checkWinState();

    }

    matchState = checkState;
}

void GameState::updateLineState(size_t outerCellUpdated, size_t innerCellUpdated){

   const std::array<LineState, NUM_CELL_COMBOS>& lines = lineStates[outerCellUpdated];
   
}

void GameState::findLineStateIndexes(LineIndexes& lineIndexes, size_t outerCellUpdated, size_t innerCellUpdated){


   for(size_t i = 0; i < NUM_CELL_COMBOS; i++){

        if(lineStates[outerCellUpdated][i] == LineState::ALIVE){
            for(size_t j = 0; j < BoardLayout::CELLS_PER_AXIS; j++){

                if(WIN_CONDITIONS[i][j] == innerCellUpdated){
                    lineIndexes.push_back(i);

                    
                }
            }
        }
   }
}

const OuterStates& GameState::getOuterStates() const{
    return outerStates;
}

MatchState GameState::getMatchState() const{
    return matchState;
}

bool GameState::matchPosition(BoardMarker m1, BoardMarker m2) const{

    if(boardMarkersNone(m1, m2)) return false;

    return m1 == m2;
}

bool GameState::matchPosition(MatchState s1, MatchState s2) const{

    if(matchStatesOngoing(s1, s2)) return false;

    return s1 == s2;
}

bool GameState::boardMarkersNone(BoardMarker m1, BoardMarker m2) const{
    return m1 == BoardMarker::NONE || m2 == BoardMarker::NONE;
}

bool GameState::matchStatesOngoing(MatchState s1, MatchState s2) const{
    return s1 == MatchState::ONGOING || s2 == MatchState::ONGOING;
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

MatchState GameState::checkDrawState(const InnerPos& inner) const{

    for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

        
    }

    return MatchState::DRAW;
}

MatchState GameState::checkDrawState() const{

    for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

        
    }

    return MatchState::DRAW;

}

MatchState GameState::assignOuterWinner(BoardMarker marker) const{

    MatchState winner = MatchState::ONGOING;

    if(marker == BoardMarker::CROSS) winner = MatchState::CROSS_WON;
    if(marker == BoardMarker::NOUGHT) winner = MatchState::NOUGHT_WON;

    return winner;
}