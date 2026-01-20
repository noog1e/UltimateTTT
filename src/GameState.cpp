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

bool GameState::findNoneBoardMarker(const InnerPos& ipos, size_t lineIndex){

    const WinConditions& wc = WIN_CONDITIONS;

    for(size_t i = 0; i < BoardLayout::CELLS_PER_AXIS; i++){

        if(ipos[wc[lineIndex][i]] == BoardMarker::NONE){
            return true;
        }
    }

    return false;
}

LineWinState GameState::confirmBoardMarker(BoardMarker marker){
    return marker == BoardMarker::NOUGHT ? LineWinState::NOUGHT_CAP : LineWinState::CROSS_CAP;
}

LineWinState GameState::confirmBoardMarker(MatchOutcome marker){
    return marker == MatchOutcome::NOUGHT_WON ? LineWinState::NOUGHT_CAP : LineWinState::CROSS_CAP;
}

LineWinState GameState::updateInnerCellLWS(const InnerPos& ipos, size_t lineIndex){

    if(!findNoneBoardMarker(ipos, lineIndex)){

        const WinConditions& wc = WIN_CONDITIONS;
        BoardMarker m1 = ipos[wc[lineIndex][0]];
        BoardMarker m2 = BoardMarker::NONE;
        int matchCount = 1;

        for(size_t i = 1; i < BoardLayout::CELLS_PER_AXIS; i++){
            m2 = ipos[wc[lineIndex][i]];
            if(m1 == m2){
                matchCount++;
            }else{
                return LineWinState::BLOCKED;
            }
        }
        
        if(matchCount == BoardLayout::CELLS_PER_AXIS){
            return confirmBoardMarker(m1);
        } //Else some sort of error?
    }
    
    return LineWinState::ALIVE;
}

bool GameState::checkLineCaptured(LineWinState lw){
    return lw == LineWinState::NOUGHT_CAP || lw == LineWinState::CROSS_CAP;
}

bool GameState::checkLineCaptured(MatchOutcome mo){
    return mo == MatchOutcome::NOUGHT_WON || mo == MatchOutcome::CROSS_WON;
}

MatchOutcome GameState::confirmMatchWinner(LineWinState lw){
    return lw == LineWinState::NOUGHT_CAP ? MatchOutcome::NOUGHT_WON : MatchOutcome::CROSS_WON; 
}

void GameState::updateOuterMatchOutcome(size_t outerCell, size_t lineIndex){

    MatchEvaluationState& outerMatch = eval.outer[outerCell];

    LineWinStates& outerLWS = outerMatch.lineWinStates;

    if(checkLineCaptured(outerLWS[lineIndex])){
        outerMatch.matchOutcome = confirmMatchWinner(outerLWS[lineIndex]);
    }else if(outerLWS[lineIndex] == LineWinState::BLOCKED){
        outerMatch.blockedLines++; //Increase the number of blocked lines

        if(outerMatch.blockedLines == NUM_CELL_COMBOS){
            outerMatch.matchOutcome = MatchOutcome::DRAW;
        }

    }
}

void GameState::updateOuterMatchEval(const InnerPos& ipos, size_t outerCell, size_t innerCell){

    //if(outerCell < 0 || innerCell < 0 ) Need enum

    MatchEvaluationState& outerMatch = eval.outer[outerCell];
    LineWinStates& outerLWS = outerMatch.lineWinStates;
    const CellWinConditions& cwc = CELL_WIN_LINES[innerCell];

    for(size_t i = 0; i < cwc.count; i++){

        size_t lineIndex = cwc.cellLines[i];

        if(outerLWS[lineIndex] == LineWinState::ALIVE){
            
            outerLWS[lineIndex] = updateInnerCellLWS(ipos, lineIndex);

            updateOuterMatchOutcome(outerCell, lineIndex);

            if(outerMatch.matchOutcome != MatchOutcome::ONGOING) break;
        }
    }
}

LineWinState GameState::updateOuterCellLWS(size_t lineIndex){

    const WinConditions& wc = WIN_CONDITIONS;
    MatchOutcome m1 = MatchOutcome::ONGOING;
    MatchOutcome m2 = MatchOutcome::ONGOING;
    int matchCount = 1;

    int m1i = 0;

    for(m1i; m1i < BoardLayout::CELLS_PER_AXIS; m1i++){
        m1 = eval.outer[wc[lineIndex][m1i]].matchOutcome;
    }

    if(m1 != MatchOutcome::ONGOING){

        for(size_t i = m1i + 1; BoardLayout::CELLS_PER_AXIS - 1; i++){

            m2 = eval.outer[wc[lineIndex][i+1]].matchOutcome;
            
            if(m2 != MatchOutcome::ONGOING){
                if(m1 == m2){
                    matchCount++;
                }else{
                    return LineWinState::BLOCKED;
                }
            }
        }
    }

    if(matchCount == BoardLayout::CELLS_PER_AXIS){
        return confirmBoardMarker(m1);
    } //Else some sort of error?
    
    return LineWinState::ALIVE;
}

void GameState::updateOverallMatchOutcome(size_t lineIndex){
    MatchEvaluationState& overallMatch = eval.overall;

    LineWinStates& overallMatchLWS = overallMatch.lineWinStates;

    if(checkLineCaptured(overallMatchLWS[lineIndex])){
        overallMatch.matchOutcome = confirmMatchWinner(overallMatchLWS[lineIndex]);
    }else if(overallMatchLWS[lineIndex] == LineWinState::BLOCKED){
        overallMatch.blockedLines++; //Increase the number of blocked lines

        if(overallMatch.blockedLines == NUM_CELL_COMBOS){
            overallMatch.matchOutcome = MatchOutcome::DRAW;
        }

    }
}

void GameState::updateOverallMatchEval(size_t outerCell){

    MatchEvaluationState& overallMatch = eval.overall;
    LineWinStates& overallLWS = overallMatch.lineWinStates;
    const CellWinConditions& cwc = CELL_WIN_LINES[outerCell];

    for(size_t i = 0; i < cwc.count; i++){

        size_t lineIndex = cwc.cellLines[i];

        if(overallLWS[lineIndex] == LineWinState::ALIVE){
            
            overallLWS[lineIndex] = updateOuterCellLWS(lineIndex);

            updateOverallMatchOutcome(lineIndex);

            if(overallMatch.matchOutcome != MatchOutcome::ONGOING) break;
        }
    }
}

void GameState::updateGameState(const InnerPos& ipos, size_t outerCell, size_t innerCell){

    const MatchEvaluationState& outerMatch = eval.outer[outerCell];

    if(outerMatch.matchOutcome == MatchOutcome::ONGOING){
        updateOuterMatchEval(ipos, outerCell, innerCell);

        if(outerMatch.matchOutcome != MatchOutcome::ONGOING){

            updateOverallMatchEval(outerCell);
        }

    } //Else some error through enum maybe?
}
