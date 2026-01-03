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

void Board::drawInnerGrid(const InnerPos& pos, size_t uRow, size_t uCol){

    size_t xO = uRow * (U_CELL_HEIGHT + U_GRID_THICKNESS) + GAP_HEIGHT;
    size_t rowCoord = L_HEIGHT + xO;
    int outer = -1;

    size_t cell = 0;

    for(xO; xO < rowCoord; xO++){

        size_t yO = uCol * (U_CELL_WIDTH + U_GRID_THICKNESS) + GAP_WIDTH;
        size_t colCoord = L_WIDTH + yO;
        int inner = 0;

        outer++;

        for(yO; yO < colCoord; yO++){

            if(inner == L_CELL_WIDTH){
                board[xO][yO] = COL_LINE;
                inner = 0;

            }else {
                
                if(outer == L_CELL_HEIGHT && (xO + 1) != rowCoord){
                    board[xO][yO] = ROW_LINE;
                }else if(inner == ((L_CELL_WIDTH - 1) / 2) && outer == ((L_CELL_HEIGHT - 1))){
                    board[xO][yO] = drawPosChar(pos[cell++]);
                } else{
                    board[xO][yO] = ' ';
                }

                inner++;
            }

        }

        if(outer == L_CELL_HEIGHT) outer = -1;
    }

    //I think this can be better optimised. Feels wrong initiating inside the loop plus the math
    //looks criminal, like someone put brisket in a brioche bun and called it a burger.

}

void Board::drawInnerGrids(const OuterPos& pos){

    size_t cell = 0;

    for(size_t i=0; i < NUM_DIM; i++){

        for(size_t j=0; j < NUM_DIM; j++){
            
            if(cell > pos.size()){
                throw std::out_of_range("Drawing inner grids - too many positions");
            }
                
            drawInnerGrid(pos[cell++], i, j);
        }
    }
}

void Board::drawOuterGrid(){

    int xO = 0;
    int xThickCount = 0;

    int yO = 0;
    int yThickCount = 0;

    for(size_t i = 0; i < U_HEIGHT; i++){

        if(yThickCount == U_GRID_THICKNESS){
            yO = 0;
            yThickCount = 0;
        }

        if(yO == U_CELL_HEIGHT){

            for(size_t j = 0; j < U_WIDTH; j = j+2){

                board[i][j] = OUTER_GRID;
            }

            yThickCount++;

        }else{

            for(size_t j = 0; j < U_WIDTH; j = j+2){

                if(xThickCount == U_GRID_THICKNESS){
                    xO = 0;
                    xThickCount = 0;
                }

                if(xO == U_CELL_WIDTH){
                    board[i][j] = OUTER_GRID;
                    xThickCount++;
                }else{
                    xO++;
                }
            }


        }

        if(yThickCount != U_GRID_THICKNESS){
            yO++;
        }
    }
}

char Board::drawPosChar(BoardMarker marker){

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

    drawOuterGrid();
    drawInnerGrids(pos);
}