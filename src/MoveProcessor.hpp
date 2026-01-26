#pragma once

#include "GameState.hpp"
#include "MarkerPositions.hpp"
#include <cstddef>

enum class MoveConstraint{
    ANY, FORCED_OUTER_CELL
};

class MoveProcessor{
    
    public:
    MoveProcessor();

    void setCurrentOuterCell(size_t cell, PosUpdate& update, const OuterMES& outerMES);
    void setMoveConstraint(MoveConstraint setConstraint);

    size_t getCurrentOuterCell() const;
    MoveConstraint getMoveConstraint() const;

    void applyPlayerMove(
        const BoardMarker marker, 
        MarkerPositions& positions, 
        GameState& gs, 
        size_t innerCell,
        PosUpdate& update
    );

    private:
    size_t currentOuterCell = 0;
    MoveConstraint constraint = MoveConstraint::FORCED_OUTER_CELL;
    
};
