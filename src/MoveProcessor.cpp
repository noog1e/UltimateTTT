#include "MoveProcessor.hpp"
#include "BoardLayout.hpp"
#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include <cstddef>

MoveProcessor::MoveProcessor(){}

void MoveProcessor::setCurrentOuterCell(size_t cell, PosUpdate& update, const OuterMES& outerMES){

    if(cell < 0 || cell >= BoardLayout::NUM_CELLS){
        update = PosUpdate::OUT_OF_BOUNDS;
    } else if(outerMES[cell].matchOutcome != MatchOutcome::ONGOING){
        constraint = MoveConstraint::ANY;
    } else{
        currentOuterCell = cell;
    }

}

BoardMarker MoveProcessor:: convertPlayerMarker(PlayerMarker pm){
    return pm == PlayerMarker::CROSS ? BoardMarker::CROSS : BoardMarker::NOUGHT;
}

void MoveProcessor::applyPlayerMove(const PlayerSlot& player, MarkerPositions& positions, GameState& gs, size_t innerCell, PosUpdate& update){
    
    if(constraint == MoveConstraint::FORCED_OUTER_CELL){
        BoardMarker marker = convertPlayerMarker(player.marker);
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