#include "board.hpp"
#include <cstddef>
#include <iostream>
#include <string>

const char OUTER_GRID = '#';
const char INNER_ROW_LINE = '_';
const char INNER_COL_LINE = '|';
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
        row.fill(SPACE);
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

void Board::drawVerticalLine(size_t xO, size_t yO, int height, char unicode, Spacing spacing){

    int space = static_cast<int>(spacing) + 1;

    for(size_t row = 0; row < height; row++){

        board[yO++][xO] = unicode;
    }
}

void Board::drawHorizontalLine(size_t xO, size_t yO, int width, char unicode, Spacing spacing){

    int space = static_cast<int>(spacing) + 1;

    for(size_t col = 0; col < width; col++){

        board[yO][xO++] = unicode;
    }
}

void Board::drawInnerGridVerticalLines(size_t xO, size_t yO){

    for(size_t i = 0; i < GRID_DIVIDERS; i++){

        xO = xO + INNER_CELL_WIDTH;

        drawVerticalLine(xO, yO, L_HEIGHT, INNER_COL_LINE, Spacing::NONE);

        xO++;
    }
}

void Board::drawInnerGridHorizontalLines(size_t xO, size_t yO){

    for(size_t i = 0; i < GRID_DIVIDERS; i++){

        yO = yO + (INNER_CELL_HEIGHT - 1);

        drawHorizontalLine(xO, yO, L_WIDTH, INNER_ROW_LINE, Spacing::NONE);

        yO++;
    }

}

void Board::drawInnerGrid(size_t xO, size_t yO){
    drawInnerGridHorizontalLines(xO, yO);
    drawInnerGridVerticalLines(xO, yO);
}

void Board::drawInnerGrids(){

    size_t xO = 0; 
    size_t yO = 0;

    for(size_t i = 0; i < CELLS_PER_AXIS; i++){

        for(size_t j = 0; j < CELLS_PER_AXIS; j++){
            
            xO = calculateInnerGrid_XOffset(i);
            yO = calculateInnerGrid_YOffset(j);
            drawInnerGrid(xO, yO);
        }        
    }

}

void Board::drawCellMarkers(const InnerPos& pos){

}

void Board::drawOuterGridVerticalLines(){

    int xO = OUTER_CELL_WIDTH;
    int yO = 0;

    for(size_t i = 0; i < GRID_DIVIDERS; i++){

        drawVerticalLine(xO, yO, U_HEIGHT, OUTER_GRID, Spacing::NONE);

        xO = xO + OUTER_CELL_WIDTH + U_GRID_THICKNESS;
    }
}

void Board::drawOuterGridHorizontalLines(){

    int xO = 0;
    int yO = OUTER_CELL_HEIGHT;

    for(size_t i = 0; i < GRID_DIVIDERS; i++){

        drawHorizontalLine(xO, yO, U_WIDTH, OUTER_GRID, Spacing::SINGLE);

        yO = yO + OUTER_CELL_HEIGHT + U_GRID_THICKNESS;
    }
}

void Board::drawOuterGrid(){

    drawOuterGridVerticalLines();
    drawOuterGridHorizontalLines();
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
    drawInnerGrids();
    drawOuterGrid();
}

size_t Board::calculateInnerGrid_XOffset(int outerRow) const{
    return SUBGRID_MARGIN_WIDTH + (outerRow * (OUTER_CELL_WIDTH + U_GRID_THICKNESS));
}

size_t Board::calculateInnerGrid_YOffset(int outerColumn) const{
    return SUBGRID_MARGIN_HEIGHT + (outerColumn * (OUTER_CELL_HEIGHT + U_GRID_THICKNESS));
}