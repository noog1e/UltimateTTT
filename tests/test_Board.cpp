#include "Board.hpp"
#include "Renderer.hpp"
#include "TestingUtilities.hpp"
#include "MarkerPositions.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <iostream>

TEST_CASE("Print Board", "[board][print]"){

    Renderer render;
    Board board;

    printBoard(board, render);

    SECTION("Update marker"){

        board.drawPositionUpdate(8, 8, drawPositionChar(BoardMarker::CROSS));
        printBoard(board, render);
    }
}