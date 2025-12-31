#include "board.hpp"
#include <cstddef>
#include <iostream>
#include <string>

const char OUTER_GRID = '#';
const char ROW_LINE = '_';
const char COL_LINE = '|';
const char SPACE = ' ';

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

const OuterPos& MarkerPositions::getMarkerPositions() const{
    return pos;
}

Board::Board(){
    clear();
}

void Board::clear(){

    for(auto& row : board){
        row.fill('-');
    }
}

const board2DArray& Board::getBoard() const{
    return board;
}

size_t Board::getHeight() const{
    return height;
}

size_t Board::getWidth() const{
    return width;
}

void Board::drawInnerGrid(const OuterPos& pos, size_t uRow, size_t uCol){

    size_t row = uRow * (U_CELL_HEIGHT + GRID_THICKNESS) + GAP_HEIGHT;
    size_t col = uCol * (U_CELL_WIDTH + GRID_THICKNESS) + GAP_WIDTH;

    for(row; row < L_HEIGHT; row++){

        for(col; col < L_WIDTH; col++){

            board[row][col] = '+';
        }
    }

}

void Board::drawInnerGrids(const OuterPos& pos){

    for(size_t i=0; i < NUM_DIM; i++){

        for(size_t j=0; j < NUM_DIM; j++){
            drawInnerGrid(pos, i, j);
        }
    }
}

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

void Board::draw(const OuterPos& pos){

        drawInnerGrids(pos);
}


/*

65 x 35

                     #                     #                      0
       |     |       #       |     |       #       |     |        1
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     2
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   3
       |     |       #       |     |       #       |     |        4
    x  |  o  |  x    #    x  |  o  |  x    #    x  |  o  |  x     5
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   6
       |     |       #       |     |       #       |     |        7
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     8
       |     |       #       |     |       #       |     |        9
                     #                     #                      10
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 11
                     #                     #                      12
       |     |       #       |     |       #       |     |        13
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     14
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   15
       |     |       #       |     |       #       |     |        16
    x  |  o  |  x    #    o  |  x  |  o    #    o  |  x  |  o     17
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   18
       |     |       #       |     |       #       |     |        19
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     20
       |     |       #       |     |       #       |     |        21
                     #                     #                      22
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 23
                     #                     #                      24
       |     |       #       |     |       #       |     |        25
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     26
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   27
       |     |       #       |     |       #       |     |        28
    x  |  o  |  x    #    o  |  x  |  o    #    o  |  x  |  o     29
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   30
       |     |       #       |     |       #       |     |        31
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     32
       |     |       #       |     |       #       |     |        32
                     #                     #                      34

01234567890123456789012345678901234567890123456789012345678901234
          1         2         3         4         5         6    
*/

/*

*/
