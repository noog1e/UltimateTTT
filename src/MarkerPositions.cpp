#include "MarkerPositions.hpp"
#include "BoardLayout.hpp"
#include <array>

namespace BL = BoardLayout;

MarkerPositions::MarkerPositions(){

    for(size_t i=0; i < BL::NUM_CELLS; i++){
        for(size_t j=0; j < BL::NUM_CELLS; j++){
            pos[i][j] = BoardMarker::NONE; 
        }
    }
}

void MarkerPositions::checkBounds(size_t outer, size_t inner, PosUpdate& update){
    
    if(outer < 0 || outer >= BL::NUM_CELLS){
        update = PosUpdate::OUT_OF_BOUNDS;
    }else if(inner < 0 || inner >= BL::NUM_CELLS){
        update = PosUpdate::OUT_OF_BOUNDS;
    }
}

void MarkerPositions::checkPosition(size_t outer, size_t inner, PosUpdate& update){
    
    BoardMarker posMarker = pos[outer][inner];
    
    if(posMarker != BoardMarker::NONE){
        update = PosUpdate::OCCUPIED;
    }else{
        update = PosUpdate::VALID;
    }
}

void MarkerPositions::updateMarkerAtPos(size_t outer, size_t inner, BoardMarker marker, PosUpdate& update){

    outer -= 1;
    inner -= 1;

    checkBounds(outer, inner, update);
    if(update != PosUpdate::OUT_OF_BOUNDS){

        if(marker != BoardMarker::NONE) checkPosition(outer, inner, update); //May implement a version where a placement takeback exists
        if(update == PosUpdate::VALID){
            pos[outer][inner] = marker;
        }
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