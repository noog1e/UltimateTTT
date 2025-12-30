#include "board.hpp"
#include <iostream>

void printBoard(const board2DArray& board, size_t height, size_t width){

    for(size_t i=0; i < height; i++){

        for(size_t j=0; j < width; j++){

            std::cout << board[i][j];
        }
    }
}

int main(){

    Board board;
    MarkerPositions markers;

    printBoard(board.getBoard(), board.getHeight(), board.getWidth());

    return 0;
}