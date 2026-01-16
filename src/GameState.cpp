#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include <cstddef>
#include <array>

namespace BL = BoardLayout;

GameState::GameState(){
    reset();
}

void GameState::reset(){
    
    if(eval.overallMatchState != MatchState::ONGOING) eval.overallMatchState = MatchState::ONGOING;

    initOverallLWS();
    initOuterMS();
    initOuterLWS();
}

void GameState::initOverallLWS(){

    for(size_t i = 0; i < NUM_CELL_COMBOS; i++){
        eval.overallLineWinStates[i] = LineWinState::ALIVE;
    }
}

void GameState::initOuterMS(){

    for(size_t i = 0; i < BL::NUM_CELLS; i++){
        eval.outerMatchStates[i] = MatchState::ONGOING;
    }
}

void GameState::initOuterLWS(){
    
    for(size_t i = 0; i < BL::NUM_CELLS; i++){
        
        for(size_t j = 0; j < NUM_CELL_COMBOS; j++){
            eval.outerLineWinStates[i][j] = LineWinState::ALIVE;
        }
    }
}

const MatchEvaluation& GameState::getMatchEvaluation() const{
    return eval;
}

LineWinState GameState::updateCellLineWinState(const InnerPos& ipos, size_t lineIndex){

    const WinConditions& wc = WIN_CONDITIONS;
    BoardMarker m1 = BoardMarker::NONE;
    BoardMarker m2 = BoardMarker::NONE;

    int matchCount = 1;

    for(size_t j = 0; j < BL::CELLS_PER_AXIS - 1; j++){

        m1 = ipos[wc[lineIndex][j]];

        if(m1 == BoardMarker::NONE) continue;

        m2 = ipos[wc[lineIndex][j+1]];

        if(m1 != m2 && m2 != BoardMarker::NONE){
            return LineWinState::BLOCKED;
        }else{
            matchCount++;
        }
    }

    if(matchCount == BL::CELLS_PER_AXIS){
        return confirmBoardMarker(m1);
    }

    return LineWinState::ALIVE;
}

LineWinState GameState::confirmBoardMarker(BoardMarker marker){
    return marker == BoardMarker::NOUGHT ? LineWinState::NOUGHT_CAP : LineWinState::CROSS_CAP;
}

void GameState::updateOuterLineWinStates(const InnerPos& ipos, size_t outerCell, size_t innerCell){

    //if(outerCell < 0 || innerCell < 0 ) Need enum

    LineWinStates& outerCellLWS = eval.outerLineWinStates[outerCell];
    const CellWinConditions& cwc = CELL_WIN_LINES[innerCell];

    for(size_t i = 0; i < cwc.count; i++){

        size_t lineIndex = cwc.cellLines[i];

        if(outerCellLWS[lineIndex] == LineWinState::ALIVE){
            
            outerCellLWS[lineIndex] = updateCellLineWinState(ipos, lineIndex);

            
        }
    }
}

void GameState::updateOuterMatchStates(size_t outerCell){

    const LineWinStates& outerCellLWS = eval.outerLineWinStates[outerCell];
    
    bool linesBlocked = true;

    for(size_t i = 0; i < NUM_CELL_COMBOS; i++){

        if(outerCellLWS[i] == LineWinState::ALIVE){
            linesBlocked = false;
            break;
        }
    }



}

void GameState::updateGameState(const InnerPos& ipos, size_t outerCell, size_t innerCell){

    updateOuterLineWinStates(ipos, outerCell, innerCell);
}
