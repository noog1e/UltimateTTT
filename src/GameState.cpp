#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include <cstddef>
#include <array>

namespace BL = BoardLayout;

GameState::GameState(){
    reset();
}

void GameState::reset(){
    
    if(overallMS != MatchState::ONGOING) overallMS = MatchState::ONGOING;

    initOuterMS();
    initOuterLWS();
}

void GameState::initOuterMS(){

    for(size_t i = 0; i < BL::NUM_CELLS; i++){
        outerMS[i] = MatchState::ONGOING;
    }
}

void GameState::initOuterLWS(){
    
    for(size_t i = 0; i < BL::NUM_CELLS; i++){
        
        for(size_t j = 0; j < NUM_CELL_COMBOS; j++){
            outerLWS[i][j] = LineWinState::ALIVE;
        }
    }
}

MatchState GameState::getOverallMatchState() const{
    return overallMS;
}

const OuterMS& GameState::getOuterMatchStates() const{
    return outerMS;
}

const OuterLWS& GameState::getOuterLineWinStates() const{
    return outerLWS;
}
