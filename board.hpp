#pragma once

#include "MarkerPositions.hpp"
#include "BoardLayout.hpp"
#include <array>
#include <cstddef>

enum class BoundsCheck{
   IN_BOUNDS, OO_BOUNDS
};

enum class Spacing{
   NONE, SINGLE, DOUBLE
};

using Board2DArray = std::array<std::array<char, BoardLayout::U_WIDTH>, BoardLayout::U_HEIGHT>;

class Board{

   public:
   Board();

   void clear();

   const Board2DArray& getBoard() const;
   size_t getHeight() const;
   size_t getWidth() const;

   void draw(const OuterPos& pos);

   private:

   Board2DArray board;
   size_t boardHeight = BoardLayout::U_HEIGHT;
   size_t boardWidth = BoardLayout::U_WIDTH;

   //Line drawing
   void drawVerticalLine(size_t xO, size_t yO, int height, char unicode, Spacing spacing);
   void drawHorizontalLine(size_t xO, size_t yO, int width, char unicode, Spacing spacing);  
   void drawInnerGridVerticalLines(size_t xO, size_t yO);
   void drawInnerGridHorizontalLines(size_t xO, size_t yO);
   void drawOuterGridVerticalLines();
   void drawOuterGridHorizontalLines();
   
   //Grid drawing
   void drawInnerGrid(size_t xO, size_t yO);
   void drawInnerGrids();
   void drawOuterGrid();
   
   //Marker drawing
   void drawMarkerPositions(const OuterPos& pos);
   void drawCellMarkers(const InnerPos& pos, int outerRow, int outerColumn);
   char drawPositionChar(BoardMarker marker) const;

   //Geometry
   size_t calculateInnerGrid_XOffset(int outerCol) const;
   size_t calculateInnerGrid_YOffset(int outerRow) const;
   size_t calculateMarkerPositions_XOffset(size_t inner_xO, int innerCol) const;
   size_t calculateMarkerPositions_YOffset(size_t inner_yO, int innerRow) const;
   
};



