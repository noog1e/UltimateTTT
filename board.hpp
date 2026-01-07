#pragma once

#include "MarkerPositions.hpp"
#include "BoardLayout.hpp"
#include <array>
#include <cstddef>

enum class DrawBoundsCheck{
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

   DrawBoundsCheck draw(const OuterPos& pos);

   private:

   Board2DArray board;
   size_t boardHeight = BoardLayout::U_HEIGHT;
   size_t boardWidth = BoardLayout::U_WIDTH;

   //Line drawing
   DrawBoundsCheck drawVerticalLine(size_t xO, size_t yO, int height, char unicode, Spacing spacing);
   DrawBoundsCheck drawHorizontalLine(size_t xO, size_t yO, int width, char unicode, Spacing spacing);  
   DrawBoundsCheck drawInnerGridVerticalLines(size_t xO, size_t yO);
   DrawBoundsCheck drawInnerGridHorizontalLines(size_t xO, size_t yO);
   DrawBoundsCheck drawOuterGridVerticalLines();
   DrawBoundsCheck drawOuterGridHorizontalLines();
   
   //Grid drawing
   DrawBoundsCheck drawInnerGrid(size_t xO, size_t yO);
   DrawBoundsCheck drawInnerGrids();
   DrawBoundsCheck drawOuterGrid();
   
   //Marker drawing
   DrawBoundsCheck drawMarkerPositions(const OuterPos& pos);
   DrawBoundsCheck drawCellMarkers(const InnerPos& pos, int outerRow, int outerColumn);
   char drawPositionChar(BoardMarker marker) const;

   //Geometry
   size_t calculateInnerGrid_XOffset(int outerCol) const;
   size_t calculateInnerGrid_YOffset(int outerRow) const;
   size_t calculateMarkerPositions_XOffset(size_t inner_xO, int innerCol) const;
   size_t calculateMarkerPositions_YOffset(size_t inner_yO, int innerRow) const;
   
};



