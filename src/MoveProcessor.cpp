#include "MoveProcessor.hpp"
#include "BoardLayout.hpp"
#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include <cstddef>
#include <cassert>

MoveProcessor::MoveProcessor(size_t startingOuterCell){

    assert(startingOuterCell < BoardLayout::NUM_CELLS);
    currentOuterCell = startingOuterCell;
}

void MoveProcessor::setCurrentOuterCell(size_t cell, const OuterMES& outerMES){

    assert(cell < BoardLayout::NUM_CELLS);

    if(outerMES[cell].matchOutcome != MatchOutcome::ONGOING){
        constraint = MoveConstraint::ANY;
    } else{
        currentOuterCell = cell;
    }

}

size_t MoveProcessor::getCurrentOuterCell() const{
    return currentOuterCell;
}

MoveConstraint MoveProcessor::getMoveConstraint() const{
    return constraint;
}

/*BoardMarker convertPlayerMarker(PlayerMarker pm){
    return pm == PlayerMarker::CROSS ? BoardMarker::CROSS : BoardMarker::NOUGHT;
} MOVE THIS*/ 

void MoveProcessor::applyPlayerMove(const BoardMarker marker, MarkerPositions& positions, GameState& gs, size_t innerCell){
    
    assert(constraint == MoveConstraint::FORCED_OUTER_CELL);

    PosUpdate update;

    positions.updateMarkerAtPos(currentOuterCell, innerCell, marker, update);

    if(update == PosUpdate::VALID){

        const InnerPos& innerPos = positions.getMarkerPositions()[currentOuterCell];
        gs.updateGameState(innerPos, currentOuterCell, innerCell);

        const MatchEvaluation& eval = gs.getMatchEvaluation();
        setCurrentOuterCell(innerCell, eval.outer);
    }

}