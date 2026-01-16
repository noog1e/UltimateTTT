#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include <iostream>
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

void GameState::updateOuterMatchEval(const InnerPos& ipos, size_t outerCell, size_t innerCell){

    //if(outerCell < 0 || innerCell < 0 ) Need enum

    MatchEvaluationState& outerMatch = eval.outer[outerCell];

    LineWinStates& outerLWS = outerMatch.lineWinStates;
    const CellWinConditions& cwc = CELL_WIN_LINES[innerCell];

    for(size_t i = 0; i < cwc.count; i++){

        size_t lineIndex = cwc.cellLines[i];

        if(outerLWS[lineIndex] == LineWinState::ALIVE){
            
            outerLWS[lineIndex] = updateCellLineWinState(ipos, lineIndex);

            //if(outerLWS[lineIndex] == LineWinState::ALIVE) break;

            updateOuterMatchOutcome(outerCell, lineIndex);
        }
    }
}

void GameState::updateOuterMatchOutcome(size_t outerCell, size_t lineIndex){

    MatchEvaluationState& outerMatch = eval.outer[outerCell];

    LineWinStates& outerLWS = outerMatch.lineWinStates;

            if(outerLWS[lineIndex] == LineWinState::BLOCKED){
                outerMatch.blockedLines++; //Increase the number of blocked lines
                
                std::cout << "block lines: " << outerMatch.blockedLines << "\n";

                if(outerMatch.blockedLines == NUM_CELL_COMBOS){
                    outerMatch.matchOutcome = MatchOutcome::DRAW;
                }

            }else if(checkLineCaptured(outerLWS[lineIndex])){
                outerMatch.matchOutcome = confirmMatchWinner(outerLWS[lineIndex]);
            }
}

void GameState::updateGameState(const InnerPos& ipos, size_t outerCell, size_t innerCell){

    const MatchEvaluationState& outerMatch = eval.outer[outerCell];

    if(outerMatch.matchOutcome == MatchOutcome::ONGOING){
        updateOuterMatchEval(ipos, outerCell, innerCell);

    } //Else some error through enum maybe?
}

bool GameState::checkLineCaptured(LineWinState lw){
    return lw == LineWinState::NOUGHT_CAP || lw == LineWinState::NOUGHT_CAP;
}

MatchOutcome GameState::confirmMatchWinner(LineWinState lw){
    return lw == LineWinState::NOUGHT_CAP ? MatchOutcome::NOUGHT_WON : MatchOutcome::CROSS_WON; 
}
