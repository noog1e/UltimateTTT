#include "board.hpp"
#include <iostream>

void printBoard(const board2DArray& board, size_t height, size_t width){

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

    int xO = board.calculateInnerGrid_XOffset(0);
    int yO = board.calculateInnerGrid_YOffset(0);

    board.drawInnerGrid(xO, yO);

    xO = board.calculateInnerGrid_XOffset(1);
    yO = board.calculateInnerGrid_YOffset(0);

    board.drawInnerGrid(xO, yO);

    xO = board.calculateInnerGrid_XOffset(2);
    yO = board.calculateInnerGrid_YOffset(0);

    board.drawInnerGrid(xO, yO);

    printBoard(board.getBoard(), U_HEIGHT, U_WIDTH);

    return 0;
}