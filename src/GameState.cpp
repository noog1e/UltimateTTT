#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include <cstddef>
#include <array>

namespace BL = BoardLayout;

GameState::GameState(){}

void GameState::reset(){
    
    MatchEvaluationState& overall = eval.overall;
    overall.matchOutcome = MatchOutcome::ONGOING;
    resetOverallLWS();
    resetOuterMS();
    resetOuterLWS();
}

void GameState::resetOverallLWS(){

    MatchEvaluationState& overall = eval.overall;
    LineWinStates& lws = overall.lineWinStates;
    
    lws.fill(LineWinState::ALIVE);

}

void GameState::resetOuterMS(){

    OuterMES& outer = eval.outer;
    
    for(auto& me : outer){
        me.matchOutcome = MatchOutcome::ONGOING;
    }
}

void GameState::resetOuterLWS(){
    
    OuterMES& cells = eval.outer;
    
    for(auto& me : cells){
        LineWinStates& lws = me.lineWinStates;
        lws.fill(LineWinState::ALIVE);
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

    MatchEvaluationState& outerMatch = eval.outer[outerCell];

    LineWinStates& outerLWS = outerMatch.lineWinStates;
    const CellWinConditions& cwc = CELL_WIN_LINES[innerCell];

    for(size_t i = 0; i < cwc.count; i++){

        size_t lineIndex = cwc.cellLines[i];

        if(outerLWS[lineIndex] == LineWinState::ALIVE){
            
            outerLWS[lineIndex] = updateCellLineWinState(ipos, lineIndex);

            
        }
    }
}

void GameState::updateOuterMatchState(size_t outerCell){

    const MatchEvaluationState& outerMatch = eval.outer[outerCell];
    const LineWinStates& outerLWS = outerMatch.lineWinStates;
    
    bool linesBlocked = true;

    for(size_t i = 0; i < NUM_CELL_COMBOS; i++){

        if(outerLWS[i] == LineWinState::ALIVE){
            linesBlocked = false;
            break;
        }
    }



}

void GameState::updateGameState(const InnerPos& ipos, size_t outerCell, size_t innerCell){

    updateOuterLineWinStates(ipos, outerCell, innerCell);
}
