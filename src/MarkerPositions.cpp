#include "MarkerPositions.hpp"
#include "BoardLayout.hpp"
#include <array>
#include <cassert>

namespace BL = BoardLayout;

MarkerPositions::MarkerPositions(){}

void MarkerPositions::checkPosition(size_t outer, size_t inner, PosUpdate& update){
    
    BoardMarker posMarker = pos[outer][inner];
    
    if(posMarker == BoardMarker::NONE){
        update = PosUpdate::VALID;
    }else{
        update = PosUpdate::OCCUPIED;
    }
}

void MarkerPositions::updateMarkerAtPos(size_t outer, size_t inner, BoardMarker marker, PosUpdate& update){

    assert(outer < BL::NUM_CELLS);
    assert(inner < BL::NUM_CELLS);
    
    if(marker != BoardMarker::NONE) checkPosition(outer, inner, update); //May implement a version where a placement takeback exists
    if(update == PosUpdate::VALID){
        pos[outer][inner] = marker;
    }
}

const OuterPos& MarkerPositions::getMarkerPositions() const{
    return pos;
}

void MarkerPositions::resetPositions(){

    for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){
        pos[i].fill(BoardMarker::NONE);
    }
}