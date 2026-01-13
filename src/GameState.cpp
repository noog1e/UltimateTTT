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

void GameState::updateOuterLineWinStates(const InnerPos& ipos, size_t outerCell, size_t innerCell){

    LineWinStates& outerCellLWS = eval.outerLineWinStates[outerCell];
    const WinConditions& wc = WIN_CONDITIONS;
    const CellWinConditions& cwc = CELL_WIN_LINES[innerCell];

    BoardMarker m1 = BoardMarker::NONE;
    BoardMarker m2 = BoardMarker::NONE;

    for(size_t i = 0; i < cwc.count; i++){

        size_t lineIndex = cwc.cellLines[i];

        if(outerCellLWS[lineIndex] == LineWinState::ALIVE){
            
            for(size_t j = 0; j < BL::CELLS_PER_AXIS - 1; i++){

                m1 = ipos[wc[lineIndex][j]];

                if(m1 == BoardMarker::NONE) continue;

                m2 = ipos[wc[lineIndex][j+1]];

                if(m1 != m2 && m2 != BoardMarker::NONE)
                    outerCellLWS[lineIndex] = LineWinState::BLOCKED;

            }
        }
    }
}
