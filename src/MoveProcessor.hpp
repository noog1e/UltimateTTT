#pragma once

#include "GameState.hpp"
#include "MarkerPositions.hpp"
#include <cstddef>

enum class MoveConstraint{
    ANY, FORCED_OUTER_CELL
};

class MoveProcessor{
    
    public:
    MoveProcessor(size_t startingOuterCell);

    void setCurrentOuterCell(size_t cell, const OuterMES& outerMES);

    size_t getCurrentOuterCell() const;
    MoveConstraint getMoveConstraint() const;

    void applyPlayerMove(
        const BoardMarker marker, 
        MarkerPositions& positions, 
        GameState& gs, 
        size_t innerCell
    );

    private:
    size_t currentOuterCell;
    MoveConstraint constraint = MoveConstraint::FORCED_OUTER_CELL;
};
