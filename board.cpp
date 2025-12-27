#include "board.hpp"
#include <cstddef>
#include <iostream>

MarkerPosition::MarkerPosition(){

    for(size_t i=0; i < OUTER_GRID_CELLS; i++){
        for(size_t j=0; j < INNER_GRID_CELLS; j++){
            pos[i][j] = BoardMarker::NONE; 
        }
    }
}

void MarkerPosition::checkBounds(size_t outer, size_t inner){
    
    if(outer < 0 || outer >= OUTER_GRID_CELLS){
        throw std::out_of_range("Outer grid position validation error -- MarkerPosition");
    }

    if(inner < 0 || inner >= INNER_GRID_CELLS){
        throw std::out_of_range("Outer grid position validation error -- MarkerPosition");
    }
}

bool MarkerPosition::checkPosition(size_t outer, size_t inner){
    return pos[outer][inner] == BoardMarker::NONE;
}

void MarkerPosition::updateMarkerAtPos(size_t outer, size_t inner){

    checkBounds(outer, inner);
    if(checkPosition(outer, inner)){
        
    }

    //Consider changing this to a boolean return
}
