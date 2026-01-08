#include "board.hpp"
#include <iostream>

void printBoard(const Board2DArray& board, size_t height, size_t width){

    for(size_t i=0; i < height; i++){

        for(size_t j=0; j < width; j++){

            std::cout << board[i][j];
        }

        std::cout << '\n';
    }
}

int main(){

    Board board;
    MarkerPositions markers;
    PosUpdate update;

    if(board.draw(markers.getMarkerPositions()) == DrawBoundsCheck::IN_BOUNDS);
        printBoard(board.getBoard(), board.getHeight(), board.getWidth());

    return 0;
}