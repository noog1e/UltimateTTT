#include "board.hpp"
#include <cstddef>
#include <iostream>
#include <string>

const char OUTER_GRID = '#';
const char ROW_LINE = '_';
const char COL_LINE = '|';
const char SPACE = ' ';


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
    return boardHeight;
}

size_t Board::getWidth() const{
    return boardWidth;
}

void Board::drawVerticalLine(size_t xO, size_t yO, int height, char unicode, size_t spacing){

    int increment = spacing + 1;

    for(size_t col = 0; col < height; col = col + increment){

        board[xO++][yO] = unicode;
    }
}

void Board::drawHorizontalLine(size_t xO, size_t yO, int width, char unicode, size_t spacing){

    int increment = spacing + 1;

    for(size_t row = 0; row < width; row = row + increment){

        board[xO][yO++] = unicode;
    }
}

void Board::drawInnerGrid(size_t xO, size_t yO){
    
}

void Board::drawInnerGrids(){

    size_t xO = 0; 
    size_t yO = 0;

    for(size_t i = 0; i < NUM_CELLS; i++){

        xO = calculateInnerGrid_XOffset(i);
        yO = calculateInnerGrid_YOffset(i);

        drawInnerGrid(xO, yO);
    }

}

void Board::drawCellMarkers(const InnerPos& pos){

}

char Board::drawPositionChar(BoardMarker marker){

    switch(marker){

        case BoardMarker::CROSS:
        return 'x'; //Make custom markers for Cross and Nought later?

        case BoardMarker::NOUGHT:
        return 'o';

        default:
        break;
    }

    return 'T'; //THIS IS T FOR TEST, Change later
}

void Board::draw(const OuterPos& pos){


}

size_t Board::calculateInnerGrid_XOffset(int outerRow) const{
    return SUBGRID_MARGIN_WIDTH + (outerRow * (INNER_CELL_WIDTH + U_GRID_THICKNESS + SUBGRID_MARGIN_WIDTH));
}

size_t Board::calculateInnerGrid_YOffset(int outerColumn) const{
    return SUBGRID_MARGIN_HEIGHT + (outerColumn * (INNER_CELL_HEIGHT + U_GRID_THICKNESS + SUBGRID_MARGIN_HEIGHT));
}