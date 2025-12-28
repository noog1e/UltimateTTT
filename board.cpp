#include "board.hpp"
#include <cstddef>
#include <iostream>

const char HASH = '#';
const char ROW_LINE = '_';
const char COL_LINE = '|';
const size_t XDIM = 65;
const size_t YDIM = 35;

MarkerPositions::MarkerPositions(){

    for(size_t i=0; i < OUTER_GRID_CELLS; i++){
        for(size_t j=0; j < INNER_GRID_CELLS; j++){
            pos[i][j] = BoardMarker::NONE; 
        }
    }
}

void MarkerPositions::checkBounds(size_t outer, size_t inner, PosUpdate& update){
    
    if(outer < 0 || outer >= OUTER_GRID_CELLS){
        update = PosUpdate::OUTER_OOB;
    }else if(inner < 0 || inner >= INNER_GRID_CELLS){
        update = PosUpdate::INNER_OOB;
    }
}

void MarkerPositions::checkPosition(size_t outer, size_t inner, PosUpdate& update){
    
    BoardMarker posMarker = pos[outer][inner];
    
    switch (posMarker){

        case BoardMarker::CROSS:
            update = PosUpdate::CROSS_TAKEN;

        case BoardMarker::NOUGHT:
            update = PosUpdate::NOUGHT_TAKEN;

        case BoardMarker::NONE:
            update = PosUpdate::VALID;
    }
}

void MarkerPositions::updateMarkerAtPos(size_t outer, size_t inner, BoardMarker marker, PosUpdate& update){

    checkBounds(outer, inner, update);
    if(update != PosUpdate::INNER_OOB && update != PosUpdate::OUTER_OOB){

        checkPosition(outer, inner, update);
        if(update == PosUpdate::VALID){
            pos[outer][inner] = marker;
        }
    }
}

const Position& MarkerPositions::getMarkerPositions() const{
    return pos;
}

Board::Board(){}

void Board::drawOuterRowDivide(){

    for(size_t i=0; i < XDIM; i++){
        if(i % 2 == 0){
            std::cout << HASH;
        } else{
            std::cout << " ";
        }
    }

    std::cout << "\n";
}

void Board::drawOuterSpace(){

    for(size_t i=0; i < XDIM; i++){
        
        if(i % 22 == 0 && i > 0){
            std::cout << HASH;
        }else {
            std::cout << " ";
        }
    }

    std::cout << "\n";
}

void Board::draw(const Position& pos){
    drawOuterSpace();
    drawOuterRowDivide();
    drawOuterSpace();
}


/*

65 x 35

                     #                     #                      1
       |     |       #       |     |       #       |     |        2
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     3
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   4
       |     |       #       |     |       #       |     |        5
    x  |  o  |  x    #    x  |  o  |  x    #    x  |  o  |  x     6
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   7
       |     |       #       |     |       #       |     |        8
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     9
       |     |       #       |     |       #       |     |        10
                     #                     #                      11
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 12 DONE
                     #                     #                      13
       |     |       #       |     |       #       |     |        14
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     15
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   16
       |     |       #       |     |       #       |     |        17
    x  |  o  |  x    #    o  |  x  |  o    #    o  |  x  |  o     18
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   19
       |     |       #       |     |       #       |     |        20
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     21
       |     |       #       |     |       #       |     |        22
                     #                     #                      23
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 24 DONE
                     #                     #                      25
       |     |       #       |     |       #       |     |        26
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     27
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   28
       |     |       #       |     |       #       |     |        29
    x  |  o  |  x    #    o  |  x  |  o    #    o  |  x  |  o     30
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   31
       |     |       #       |     |       #       |     |        32
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     33
       |     |       #       |     |       #       |     |        34
                     #                     #                      35

12345678901234567890123456789012345678901234567890123456789012345
         1         2         3         4         5         6    
*/
