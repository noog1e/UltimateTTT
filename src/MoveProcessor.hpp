#pragma once

#include "GameState.hpp"
#include "MarkerPositions.hpp"
#include "Player.hpp"
#include <cstddef>

class MoveProcessor{
    
    public:
    MoveProcessor();

    void applyPlayerMove(const PlayerSlot& player, MarkerPositions& positions, GameState& gs, size_t innerCell);

    private:
    
    
};
