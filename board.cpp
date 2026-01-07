#include "board.hpp"
#include "MarkerPositions.hpp"

#include <cstddef>
#include <iostream>
#include <string>

namespace {
    constexpr char OUTER_GRID = '#';
    constexpr char INNER_ROW_LINE = '_';
    constexpr char INNER_COL_LINE = '|';
    constexpr char SPACE = ' ';
}

namespace BL = BoardLayout;

Board::Board(){
    clear();
}

void Board::clear(){

    for(auto& row : board){
        row.fill(SPACE);
    }
}

const Board2DArray& Board::getBoard() const{
    return board;
}

size_t Board::getHeight() const{
    return boardHeight;
}

size_t Board::getWidth() const{
    return boardWidth;
}

DrawBoundsCheck Board::drawVerticalLine(size_t xO, size_t yO, int height, char unicode, Spacing spacing){

    if(height > boardHeight || height < 0) return DrawBoundsCheck::OO_BOUNDS;

    //int space = static_cast<int>(spacing) + 1; //TODO figure out how to do spacing (currently not used)

    for(size_t row = 0; row < height; row++){

        board[yO++][xO] = unicode;
    }

    return DrawBoundsCheck::IN_BOUNDS;
}

DrawBoundsCheck Board::drawHorizontalLine(size_t xO, size_t yO, int width, char unicode, Spacing spacing){

    if(width > boardWidth || width < 0) return DrawBoundsCheck::OO_BOUNDS;
    //int space = static_cast<int>(spacing) + 1; //TODO figure out how to do spacing (currently not used)

    for(size_t col = 0; col < width; col++){

        board[yO][xO++] = unicode;
    }

    return DrawBoundsCheck::IN_BOUNDS;
}

DrawBoundsCheck Board::drawInnerGridVerticalLines(size_t xO, size_t yO){

    for(size_t i = 0; i < BL::GRID_DIVIDERS; i++){

        xO = xO + BL::INNER_CELL_WIDTH;

        if(drawVerticalLine(xO, yO, BL::L_HEIGHT, INNER_COL_LINE, Spacing::NONE) ==
            DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;

        xO++;
    }

    return DrawBoundsCheck::IN_BOUNDS;
}

DrawBoundsCheck Board::drawInnerGridHorizontalLines(size_t xO, size_t yO){

    for(size_t i = 0; i < BL::GRID_DIVIDERS; i++){

        yO = yO + (BL::INNER_CELL_HEIGHT - 1);

        if(drawHorizontalLine(xO, yO, BL::L_WIDTH, INNER_ROW_LINE, Spacing::NONE) ==
            DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;;

        yO++;
    }

    return DrawBoundsCheck::IN_BOUNDS;
}

DrawBoundsCheck Board::drawInnerGrid(size_t xO, size_t yO){
    if(drawInnerGridHorizontalLines(xO, yO) ==
            DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;

    if(drawInnerGridVerticalLines(xO, yO) ==
            DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;;

    return DrawBoundsCheck::IN_BOUNDS;
}

DrawBoundsCheck Board::drawInnerGrids(){

    size_t xO = 0; 
    size_t yO = 0;

    for(size_t i = 0; i < BL::CELLS_PER_AXIS; i++){

        for(size_t j = 0; j < BL::CELLS_PER_AXIS; j++){
            
            xO = calculateInnerGrid_XOffset(i);
            yO = calculateInnerGrid_YOffset(j);
            if(drawInnerGrid(xO, yO) ==
                DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;
        }        
    }

    return DrawBoundsCheck::IN_BOUNDS;

}

DrawBoundsCheck Board::drawOuterGridVerticalLines(){

    int xO = BL::OUTER_CELL_WIDTH;
    int yO = 0;

    for(size_t i = 0; i < BL::GRID_DIVIDERS; i++){

        if(drawVerticalLine(xO, yO, BL::U_HEIGHT, OUTER_GRID, Spacing::NONE) ==
            DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;

        xO = xO + BL::OUTER_CELL_WIDTH + BL::U_GRID_THICKNESS;
    }

    return DrawBoundsCheck::IN_BOUNDS;
}

DrawBoundsCheck Board::drawOuterGridHorizontalLines(){

    int xO = 0;
    int yO = BL::OUTER_CELL_HEIGHT;

    for(size_t i = 0; i < BL::GRID_DIVIDERS; i++){

        if(drawHorizontalLine(xO, yO, BL::U_WIDTH, OUTER_GRID, Spacing::SINGLE) ==
            DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;;

        yO = yO + BL::OUTER_CELL_HEIGHT + BL::U_GRID_THICKNESS;
    }

    return DrawBoundsCheck::IN_BOUNDS;
}

DrawBoundsCheck Board::drawOuterGrid(){

    if(drawOuterGridVerticalLines() ==
            DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;

    if(drawOuterGridHorizontalLines()==
            DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;

    return DrawBoundsCheck::IN_BOUNDS;
}


DrawBoundsCheck Board::drawMarkerPositions(const OuterPos& pos){
    
    int outerCell = 0;

    for(size_t i = 0; i < BL::CELLS_PER_AXIS; i++){

        for(size_t j = 0; j < BL::CELLS_PER_AXIS; j++){

            outerCell = (BL::CELLS_PER_AXIS * i) + j; 

            if(drawCellMarkers(pos[outerCell], j, i) ==
            DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;
        }
    }

    return DrawBoundsCheck::IN_BOUNDS;
}

DrawBoundsCheck Board::drawCellMarkers(const InnerPos& pos, int outerColumn, int outerRow){

    if(outerColumn >= BL::CELLS_PER_AXIS ||
       outerRow >= BL::CELLS_PER_AXIS) 
       return DrawBoundsCheck::OO_BOUNDS;

    if(outerColumn < 0 ||
       outerRow < 0)
       return DrawBoundsCheck::OO_BOUNDS;

    size_t xO = calculateInnerGrid_XOffset(outerColumn); 
    size_t yO = calculateInnerGrid_YOffset(outerRow);

    size_t innerCell = 0;

    for(size_t i = 0; i < BL::CELLS_PER_AXIS; i++){

        for(size_t j = 0; j < BL::CELLS_PER_AXIS; j++){
            
            size_t x1O = calculateMarkerPositions_XOffset(xO, j);
            size_t y1O = calculateMarkerPositions_YOffset(yO, i);

            innerCell = (BL::CELLS_PER_AXIS * i) + j;

            //std::cout << "x: " << x1O << " y: " << y1O << "\n\n";     //DEBUG

            board[y1O][x1O] = drawPositionChar(pos[innerCell]);
        }        
    }

    return DrawBoundsCheck::IN_BOUNDS;
}

char Board::drawPositionChar(BoardMarker marker) const{

    switch(marker){

        case BoardMarker::CROSS:
        return 'x'; //Make custom markers for Cross and Nought later?

        case BoardMarker::NOUGHT:
        return 'o';

        default:
        break;
    }

    return SPACE;
}

DrawBoundsCheck Board::draw(const OuterPos& pos){
    
    if(drawInnerGrids() ==
            DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;
    
    if(drawOuterGrid() ==
            DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;

    if(drawMarkerPositions(pos) ==
            DrawBoundsCheck::OO_BOUNDS) return DrawBoundsCheck::OO_BOUNDS;

    return DrawBoundsCheck::IN_BOUNDS;
}

size_t Board::calculateInnerGrid_XOffset(int outerCol) const{
    return BL::SUBGRID_MARGIN_WIDTH + (outerCol * (BL::OUTER_CELL_WIDTH + BL::U_GRID_THICKNESS));
}

size_t Board::calculateInnerGrid_YOffset(int outerRow) const{
    return BL::SUBGRID_MARGIN_HEIGHT + (outerRow * (BL::OUTER_CELL_HEIGHT + BL::U_GRID_THICKNESS));
}

size_t Board::calculateMarkerPositions_XOffset(size_t inner_xO, int innerCol) const{
    //std::cout << "inner_xO " << inner_xO << " innerCol " << innerCol << "\n";     //DEBUG 
    return inner_xO + BL::INNER_CELL_CENTRE_X + (innerCol * (BL::INNER_CELL_WIDTH + BL::L_GRID_THICKNESS));
}

size_t Board::calculateMarkerPositions_YOffset(size_t inner_yO, int innerRow) const{
    //std::cout << "inner_yO " << inner_yO << " innerRow " << innerRow << "\n";     //DEBUG 
    return inner_yO + BL::INNER_CELL_CENTRE_Y + (innerRow * (BL::INNER_CELL_HEIGHT - 1 + BL::L_GRID_THICKNESS));
}