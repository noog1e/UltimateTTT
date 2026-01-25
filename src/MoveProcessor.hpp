#pragma once

#include "GameState.hpp"
#include "MarkerPositions.hpp"
#include "Player.hpp"
#include <cstddef>

class MoveProcessor{
    
    public:
    MoveProcessor();

    void setCurrentOuterCell(size_t cell, PosUpdate& update, const OuterMES& outerMES);
    
    void applyPlayerMove(
        const PlayerSlot& player, 
        MarkerPositions& positions, 
        GameState& gs, 
        size_t innerCell,
        PosUpdate& update
    );

    private:
    size_t currentOuterCell = 0;

    BoardMarker convertPlayerMarker(PlayerMarker pm);
    
};
