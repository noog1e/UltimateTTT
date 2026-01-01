#pragma once

#include <array>
#include <cstddef>
#include <string>

static constexpr size_t NUM_DIM = 3;
static constexpr size_t NUM_CELLS = NUM_DIM * NUM_DIM;

static constexpr size_t U_HEIGHT = 35;
static constexpr size_t U_WIDTH = 65;

static constexpr size_t L_HEIGHT = 9;
static constexpr size_t L_WIDTH = 17;
static constexpr size_t GAP_HEIGHT = 1;
static constexpr size_t GAP_WIDTH = 2;

static constexpr size_t U_CELL_HEIGHT = L_HEIGHT + (2 * GAP_HEIGHT);
static constexpr size_t U_CELL_WIDTH = L_WIDTH + (2 * GAP_WIDTH);

static constexpr size_t L_CELL_HEIGHT = (L_HEIGHT - (NUM_DIM - 1)) / NUM_DIM;
static constexpr size_t L_CELL_WIDTH = (L_WIDTH - (NUM_DIM - 1)) / NUM_DIM;

static constexpr size_t U_GRID_THICKNESS = 1;
static constexpr size_t L_GRID_THICKNESS = 1;

using board2DArray = std::array<std::array<char, U_WIDTH>, U_HEIGHT>;

enum class BoardMarker{
    NOUGHT, CROSS, NONE
};

enum class PosUpdate{
    VALID, CROSS_TAKEN, NOUGHT_TAKEN, OUTER_OOB, INNER_OOB 
};

using InnerPos = std::array<BoardMarker, NUM_CELLS>;
using OuterPos = std::array<InnerPos, NUM_CELLS>;

class MarkerPositions{

    public:
    MarkerPositions();

    void updateMarkerAtPos(size_t outer, size_t inner, BoardMarker marker, PosUpdate& update);
    const OuterPos& getMarkerPositions() const;

    private:
    OuterPos pos;

    void checkBounds(size_t outer, size_t inner, PosUpdate& update);
    void checkPosition(size_t outer, size_t inner, PosUpdate& update);
};

class Board{

    public:
    Board();
    //Board(size_t )

    void clear();

    const board2DArray& getBoard() const;
    size_t getHeight() const;
    size_t getWidth() const;

    void draw(const OuterPos& pos);

    private:
    board2DArray board;
    size_t height = U_HEIGHT;
    size_t width = U_WIDTH;
    
    void drawInnerGrid(const OuterPos& pos, size_t uRow, size_t uCol);
    void drawInnerGrids(const OuterPos& pos);
    std::string drawPosChar(BoardMarker marker);
};

/*

65 x 35

                     #                     #                      0
       |     |       #       |     |       #       |     |        1
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     2
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   3
       |     |       #       |     |       #       |     |        4
    x  |  o  |  x    #    x  |  o  |  x    #    x  |  o  |  x     5
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   6
       |     |       #       |     |       #       |     |        7
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     8
       |     |       #       |     |       #       |     |        9
                     #                     #                      10
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 11
                     #                     #                      12
       |     |       #       |     |       #       |     |        13
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     14
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   15
       |     |       #       |     |       #       |     |        16
    x  |  o  |  x    #    o  |  x  |  o    #    o  |  x  |  o     17
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   18
       |     |       #       |     |       #       |     |        19
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     20
       |     |       #       |     |       #       |     |        21
                     #                     #                      22
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 23
                     #                     #                      24
       |     |       #       |     |       #       |     |        25
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     26
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   27
       |     |       #       |     |       #       |     |        28
    x  |  o  |  x    #    o  |  x  |  o    #    o  |  x  |  o     29
  _____|_____|_____  #  _____|_____|_____  #  _____|_____|_____   30
       |     |       #       |     |       #       |     |        31
    o  |  x  |  o    #    o  |  x  |  o    #    o  |  x  |  o     32
       |     |       #       |     |       #       |     |        32
                     #                     #                      34

01234567890123456789012345678901234567890123456789012345678901234
          1         2         3         4         5         6    
*/

