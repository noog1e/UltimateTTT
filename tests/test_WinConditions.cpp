#include <catch2/catch_test_macros.hpp>
#include "BoardLayout.hpp"
#include "GameState.hpp"

TEST_CASE("Check CELL_WIN_LINES[0] have correct values", "[win]"){

    const CellWinConditions& cellLines = CELL_WIN_LINES[0];
    
    REQUIRE(cellLines.count == 3);
    REQUIRE(cellLines.cellLines[0] == 0);
    REQUIRE(cellLines.cellLines[1] == 3);
    REQUIRE(cellLines.cellLines[2] == 6);
}

TEST_CASE("Check CELL_WIN_LINES[1] have correct values", "[win]"){

    const CellWinConditions& cellLines = CELL_WIN_LINES[1];
    
    REQUIRE(cellLines.count == 2);
    REQUIRE(cellLines.cellLines[0] == 0);
    REQUIRE(cellLines.cellLines[1] == 4);
}

TEST_CASE("Check CELL_WIN_LINES[2] have correct values", "[win]"){

    const CellWinConditions& cellLines = CELL_WIN_LINES[2];
    
    REQUIRE(cellLines.count == 3);
    REQUIRE(cellLines.cellLines[0] == 0);
    REQUIRE(cellLines.cellLines[1] == 5);
    REQUIRE(cellLines.cellLines[2] == 7);
}

TEST_CASE("Check CELL_WIN_LINES[3] have correct values", "[win]"){

    const CellWinConditions& cellLines = CELL_WIN_LINES[3];
    
    REQUIRE(cellLines.count == 2);
    REQUIRE(cellLines.cellLines[0] == 1);
    REQUIRE(cellLines.cellLines[1] == 3);
}

TEST_CASE("Check CELL_WIN_LINES[4] have correct values", "[win]"){

    const CellWinConditions& cellLines = CELL_WIN_LINES[4];
    
    REQUIRE(cellLines.count == 4);
    REQUIRE(cellLines.cellLines[0] == 1);
    REQUIRE(cellLines.cellLines[1] == 4);
    REQUIRE(cellLines.cellLines[2] == 6);
    REQUIRE(cellLines.cellLines[3] == 7);
}

TEST_CASE("Check CELL_WIN_LINES[5] have correct values", "[win]"){

    const CellWinConditions& cellLines = CELL_WIN_LINES[5];
    
    REQUIRE(cellLines.count == 2);
    REQUIRE(cellLines.cellLines[0] == 1);
    REQUIRE(cellLines.cellLines[1] == 5);
}

TEST_CASE("Check CELL_WIN_LINES[6] have correct values", "[win]"){

    const CellWinConditions& cellLines = CELL_WIN_LINES[6];
    
    REQUIRE(cellLines.count == 3);
    REQUIRE(cellLines.cellLines[0] == 2);
    REQUIRE(cellLines.cellLines[1] == 3);
    REQUIRE(cellLines.cellLines[2] == 7);
}

TEST_CASE("Check CELL_WIN_LINES[7] have correct values", "[win]"){

    const CellWinConditions& cellLines = CELL_WIN_LINES[7];
    
    REQUIRE(cellLines.count == 2);
    REQUIRE(cellLines.cellLines[0] == 2);
    REQUIRE(cellLines.cellLines[1] == 4);
}

TEST_CASE("Check CELL_WIN_LINES[8] have correct values", "[win]"){

    const CellWinConditions& cellLines = CELL_WIN_LINES[8];
    
    REQUIRE(cellLines.count == 3);
    REQUIRE(cellLines.cellLines[0] == 2);
    REQUIRE(cellLines.cellLines[1] == 5);
    REQUIRE(cellLines.cellLines[2] == 6);
}