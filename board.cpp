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

    size_t xO = uRow * (U_CELL_HEIGHT + U_GRID_THICKNESS) + GAP_HEIGHT;
    size_t rowCoord = L_HEIGHT + xO;
    int outer = -1;

    for(xO; xO < rowCoord; xO++){

        size_t yO = uCol * (U_CELL_WIDTH + U_GRID_THICKNESS) + GAP_WIDTH;
        size_t colCoord = L_WIDTH + yO;
        int inner = 0;

        outer++;

        for(yO; yO < colCoord; yO++){

            if(inner == L_CELL_WIDTH){
                board[xO][yO] = COL_LINE;
                inner = 0;
            }else{
                
                if(outer == L_CELL_HEIGHT && (xO + 1) != rowCoord){
                    board[xO][yO] = ROW_LINE;
                }else{
                    board[xO][yO] = ' ';
                }

                inner++;
            }

        }

        if(outer == L_CELL_HEIGHT) outer = -1;
    }

    //I think this can be better optimised. Feels wrong initiating inside the loop

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