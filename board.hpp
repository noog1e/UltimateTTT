#pragma once

#include <array>
#include <cstddef>
#include <string>

static constexpr int CELLS_PER_AXIS = 3;
static constexpr int NUM_CELLS = CELLS_PER_AXIS * CELLS_PER_AXIS;

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

static constexpr int GRID_DIVIDERS = CELLS_PER_AXIS - 1;
static constexpr int SUBGRID_MARGIN_WIDTH = 2;
static constexpr int SUBGRID_MARGIN_HEIGHT = 1;
static constexpr int INNER_CELL_WIDTH = 5;
static constexpr int INNER_CELL_HEIGHT = 3;
static constexpr int OUTER_CELL_WIDTH = 21;
static constexpr int OUTER_CELL_HEIGHT = 11;


static constexpr int U_HEIGHT = 35;    // Default Outer Height
static constexpr int U_WIDTH = 65;     // Default Outer Width

static constexpr int L_HEIGHT = 9;     // Default Inner Height
static constexpr int L_WIDTH = 17;     // Default Inner Width


static constexpr int U_GRID_THICKNESS = 1;   
static constexpr int L_GRID_THICKNESS = 1;

using board2DArray = std::array<std::array<char, U_WIDTH>, U_HEIGHT>;

enum class Spacing{
   NONE, SINGLE, DOUBLE
};

class Board{

   public:
   Board();
   //Board(size_t height, size_t width)

   void clear();

   const board2DArray& getBoard() const;
   size_t getHeight() const;
   size_t getWidth() const;

   void draw(const OuterPos& pos);

   //PRIVATE LATER
   void drawVerticalLine(size_t xO, size_t yO, int height, char unicode, Spacing spacing);
   void drawHorizontalLine(size_t xO, size_t yO, int width, char unicode, Spacing spacing);
   
   void drawInnerGridVerticalLines(size_t xO, size_t yO);
   void drawInnerGridHorizontalLines(size_t xO, size_t yO);
   void drawInnerGrid(size_t xO, size_t yO);
   void drawInnerGrids();
   
   void drawOuterGridVerticalLines();
   void drawOuterGridHorizontalLines();
   void drawOuterGrid();
   
   void drawMarkerPositions(const OuterPos& pos);
   void drawCellMarkers(const InnerPos& pos);
   char drawPositionChar(BoardMarker marker);

   size_t calculateInnerGrid_XOffset(int outerRow) const;
   size_t calculateInnerGrid_YOffset(int outerColumn) const;

   private:

   board2DArray board;
   size_t boardHeight = U_HEIGHT;
   size_t boardWidth = U_WIDTH;
   
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

