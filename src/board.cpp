#include "Board.hpp"
#include "MarkerPositions.hpp"

#include <cstddef>
#include <iostream>
#include <string>
#include <cassert>

namespace {
    constexpr char OUTER_GRID = '#';
    constexpr char INNER_ROW_LINE = '_';
    constexpr char INNER_COL_LINE = '|';
    constexpr char SPACE = ' ';
}

namespace BL = BoardLayout;

Board::Board(){
    draw();
}

void Board::clear(){

    clearMarkerPositions();
}

const BoardView& Board::getBoard() const{
    return board;
}

size_t Board::getHeight() const{
    return boardHeight;
}

size_t Board::getWidth() const{
    return boardWidth;
}

void Board::drawEmpty(){

    for(auto& row : board){
        for(auto& elem : row){
            elem = SPACE;
        }
    }
}

void Board::drawVerticalLine(size_t xO, size_t yO, size_t height, char unicode, Spacing spacing){

    assert (height <= boardHeight);

    //size_t space = static_cast<size_t>(spacing) + 1; //TODO figure out how to do spacing (currently not used)

    for(size_t row = 0; row < height; row++){

        board[yO++][xO] = unicode;
    }
}

void Board::drawHorizontalLine(size_t xO, size_t yO, size_t width, char unicode, Spacing spacing){

    assert (width <= boardWidth);
    //size_t space = static_cast<size_t>(spacing) + 1; //TODO figure out how to do spacing (currently not used)

    for(size_t col = 0; col < width; col++){
        board[yO][xO++] = unicode;
    }
}

void Board::drawInnerGridVerticalLines(size_t xO, size_t yO){

    for(size_t i = 0; i < BL::GRID_DIVIDERS; i++){

        xO = xO + BL::INNER_CELL_WIDTH;
        drawVerticalLine(xO, yO, BL::L_HEIGHT, INNER_COL_LINE, Spacing::NONE);
        xO++;
    }
}

void Board::drawInnerGridHorizontalLines(size_t xO, size_t yO){

    for(size_t i = 0; i < BL::GRID_DIVIDERS; i++){

        yO = yO + (BL::INNER_CELL_HEIGHT - 1);
        drawHorizontalLine(xO, yO, BL::L_WIDTH, INNER_ROW_LINE, Spacing::NONE);
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

    for(size_t i = 0; i < BL::CELLS_PER_AXIS; i++){

        for(size_t j = 0; j < BL::CELLS_PER_AXIS; j++){
            
            xO = calculateInnerGrid_XOffset(i);
            yO = calculateInnerGrid_YOffset(j);
            drawInnerGrid(xO, yO);
        }        
    }
}

void Board::drawOuterGridVerticalLines(){

    size_t xO = BL::OUTER_CELL_WIDTH;
    size_t yO = 0;

    for(size_t i = 0; i < BL::GRID_DIVIDERS; i++){

        drawVerticalLine(xO, yO, BL::U_HEIGHT, OUTER_GRID, Spacing::NONE);
        xO = xO + BL::OUTER_CELL_WIDTH + BL::U_GRID_THICKNESS;
    }
}

void Board::drawOuterGridHorizontalLines(){

    size_t xO = 0;
    size_t yO = BL::OUTER_CELL_HEIGHT;

    for(size_t i = 0; i < BL::GRID_DIVIDERS; i++){

        drawHorizontalLine(xO, yO, BL::U_WIDTH, OUTER_GRID, Spacing::SINGLE);
        yO = yO + BL::OUTER_CELL_HEIGHT + BL::U_GRID_THICKNESS;
    }
}

void Board::drawOuterGrid(){

    drawOuterGridVerticalLines();
    drawOuterGridHorizontalLines();
}


void Board::clearMarkerPositions(){

    for(size_t i = 0; i < BL::CELLS_PER_AXIS; i++){

        for(size_t j = 0; j < BL::CELLS_PER_AXIS; j++){
            clearCellMarkers(j, i);
        }
    }
}

void Board::clearCellMarkers(size_t outerColumn, size_t outerRow){

    assert(outerColumn < BL::CELLS_PER_AXIS);
    assert(outerRow < BL::CELLS_PER_AXIS);

    size_t xO = calculateInnerGrid_XOffset(outerColumn); 
    size_t yO = calculateInnerGrid_YOffset(outerRow);

    size_t innerCell = 0;

    for(size_t i = 0; i < BL::CELLS_PER_AXIS; i++){

        for(size_t j = 0; j < BL::CELLS_PER_AXIS; j++){
            
            size_t x1O = calculateMarkerPositions_XOffset(xO, j);
            size_t y1O = calculateMarkerPositions_YOffset(yO, i);

            innerCell = (BL::CELLS_PER_AXIS * i) + j;

            //std::cout << "x: " << x1O << " y: " << y1O << "\n\n";     //DEBUG

            board[y1O][x1O] = SPACE;
        }        
    }
}

size_t Board::calculateColumn(size_t cell){
    return cell % 3;
}

size_t Board::calculateRow(size_t cell){
    
    if(cell < 3){
        return 0;
    }else if(cell >= 3 && cell <= 5){
        return 1;
    }

    return 2;
}

void Board::drawPositionUpdate(size_t outerCell, size_t innerCell, char marker){

    assert(innerCell < BL::NUM_CELLS);
    assert(outerCell < BL::NUM_CELLS);

    size_t outerColumn = calculateColumn(outerCell);
    size_t outerRow = calculateRow(outerCell);

    size_t xO = calculateInnerGrid_XOffset(outerColumn); 
    size_t yO = calculateInnerGrid_YOffset(outerRow);

    size_t innerColumn = calculateColumn(innerCell);
    size_t innerRow = calculateRow(innerCell);

    size_t x1O = calculateMarkerPositions_XOffset(xO, innerColumn);
    size_t y1O = calculateMarkerPositions_YOffset(yO, innerRow);

    board[y1O][x1O] = marker;

}

size_t Board::calculateInnerGrid_XOffset(size_t outerCol) const{
    return BL::SUBGRID_MARGIN_WIDTH + (outerCol * (BL::OUTER_CELL_WIDTH + BL::U_GRID_THICKNESS));
}

size_t Board::calculateInnerGrid_YOffset(size_t outerRow) const{
    return BL::SUBGRID_MARGIN_HEIGHT + (outerRow * (BL::OUTER_CELL_HEIGHT + BL::U_GRID_THICKNESS));
}

size_t Board::calculateMarkerPositions_XOffset(size_t inner_xO, size_t innerCol) const{
    //std::cout << "inner_xO " << inner_xO << " innerCol " << innerCol << "\n";     //DEBUG 
    return inner_xO + BL::INNER_CELL_CENTRE_X + (innerCol * (BL::INNER_CELL_WIDTH + BL::L_GRID_THICKNESS));
}

size_t Board::calculateMarkerPositions_YOffset(size_t inner_yO, size_t innerRow) const{
    //std::cout << "inner_yO " << inner_yO << " innerRow " << innerRow << "\n";     //DEBUG 
    return inner_yO + BL::INNER_CELL_CENTRE_Y + (innerRow * (BL::INNER_CELL_HEIGHT - 1 + BL::L_GRID_THICKNESS));
}

void Board::draw(){
    drawEmpty();
    drawInnerGrids();
    drawOuterGrid();
}