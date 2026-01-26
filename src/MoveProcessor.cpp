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

void MoveProcessor::setCurrentOuterCell(size_t cell, PosUpdate& update, const OuterMES& outerMES){

    if(cell >= BoardLayout::NUM_CELLS){
        update = PosUpdate::OUT_OF_BOUNDS;
    } else if(outerMES[cell].matchOutcome != MatchOutcome::ONGOING){
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

void MoveProcessor::applyPlayerMove(const BoardMarker marker, MarkerPositions& positions, GameState& gs, size_t innerCell, PosUpdate& update){
    
    if(constraint == MoveConstraint::FORCED_OUTER_CELL){
        positions.updateMarkerAtPos(currentOuterCell, innerCell, marker, update);

        if(update == PosUpdate::VALID){

            const InnerPos& innerPos = positions.getMarkerPositions()[currentOuterCell];
            gs.updateGameState(innerPos, currentOuterCell, innerCell);

            const MatchEvaluation& eval = gs.getMatchEvaluation();
            setCurrentOuterCell(innerCell, update, eval.outer);
        }
    } else{
        update = PosUpdate::OCCUPIED;
    }

}