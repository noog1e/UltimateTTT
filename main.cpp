#include "board.hpp"

int main(){

    Board board;
    MarkerPositions markers;

    board.draw(markers.getMarkerPositions());

    return 0;
}