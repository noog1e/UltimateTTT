#include "board.hpp"
#include <cstddef>
#include <iostream>
#include <string>

const char OUTER_GRID = '#';
const char ROW_LINE = '_';
const char COL_LINE = '|';
const char SPACE = ' ';
const size_t OUTER_XDIM = 65;
const size_t OUTER_YDIM = 35;
const size_t INNER_XDIM = 17;
const size_t INNER_YDIM = 11;

 // 3x3

MarkerPositions::MarkerPositions(){

    for(size_t i=0; i < NUM_CELLS; i++){
        for(size_t j=0; j < NUM_CELLS; j++){
            pos[i][j] = BoardMarker::NONE; 
        }
    }
}

void MarkerPositions::checkBounds(size_t outer, size_t inner, PosUpdate& update){
    
    if(outer < 0 || outer >= NUM_CELLS){
        update = PosUpdate::OUTER_OOB;
    }else if(inner < 0 || inner >= NUM_CELLS){
        update = PosUpdate::INNER_OOB;
    }
}

void MarkerPositions::checkPosition(size_t outer, size_t inner, PosUpdate& update){
    
    BoardMarker posMarker = pos[outer][inner];
    
    switch (posMarker){

        case BoardMarker::CROSS:
            update = PosUpdate::CROSS_TAKEN;
            break;

        case BoardMarker::NOUGHT:
            update = PosUpdate::NOUGHT_TAKEN;
            break;

        case BoardMarker::NONE:
            update = PosUpdate::VALID;
            break;
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

const OuterGrid& MarkerPositions::getMarkerPositions() const{
    return pos;
}

Board::Board(){}

std::string Board::drawPosChar(BoardMarker marker){

    switch(marker){

        case BoardMarker::CROSS:
        return "x"; //Make custom markers for Cross and Nought later?

        case BoardMarker::NOUGHT:
        return "o";

        default:
        break;
    }

    return "T"; //THIS IS T FOR TEST, Change later
}

void Board::draw(const OuterGrid& pos){


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
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 12
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
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 24
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
