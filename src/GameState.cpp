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

