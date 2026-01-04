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

    board.drawHorizontalLine(0, 0, U_WIDTH, '#', 0);
    board.drawVerticalLine(0, 0, U_HEIGHT, '#', 0);
    printBoard(board.getBoard(), U_HEIGHT, U_WIDTH);

    return 0;
}