#pragma once

#include "MarkerPositions.hpp"
#include "BoardLayout.hpp"
#include <array>
#include <cstddef>

enum class Spacing{
   NONE, SINGLE, DOUBLE
};

using BoardView = std::array<std::array<char, BoardLayout::U_WIDTH>, BoardLayout::U_HEIGHT>;

class Board{

   public:
   Board();

   void clear();
   void drawPositionUpdate(size_t outerCell, size_t innerCell, char marker);
   void drawFillOuterCell(size_t outerCell, char marker);

   const BoardView& getBoard() const;
   size_t getHeight() const;
   size_t getWidth() const;

   private:

   BoardView board;
   size_t boardHeight = BoardLayout::U_HEIGHT;
   size_t boardWidth = BoardLayout::U_WIDTH;

   //Overall Draw
   void draw();

   //Line drawing
   void drawEmpty();
   void drawVerticalLine(size_t xO, size_t yO, size_t height, char unicode, Spacing spacing);
   void drawHorizontalLine(size_t xO, size_t yO, size_t width, char unicode, Spacing spacing);  
   void drawInnerGridVerticalLines(size_t xO, size_t yO);
   void drawInnerGridHorizontalLines(size_t xO, size_t yO);
   void drawOuterGridVerticalLines();
   void drawOuterGridHorizontalLines();
   
   //Grid drawing (setup)
   void drawInnerGrid(size_t xO, size_t yO);
   void drawInnerGrids();
   void drawOuterGrid();
   
   //Marker clearing
   void clearMarkerPositions();
   void clearCellMarkers(size_t outerRow, size_t outerColumn);

   //Geometry
   size_t calculateInnerGrid_XOffset(size_t outerCol) const;
   size_t calculateInnerGrid_YOffset(size_t outerRow) const;
   size_t calculateMarkerPositions_XOffset(size_t inner_xO, size_t innerCol) const;
   size_t calculateMarkerPositions_YOffset(size_t inner_yO, size_t innerRow) const;
   size_t calculateColumn(size_t cell);
   size_t calculateRow(size_t cell);
};



