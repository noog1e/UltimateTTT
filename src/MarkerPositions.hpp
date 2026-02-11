#pragma once

#include "BoardLayout.hpp"
#include <cstddef>
#include <array>

enum class PosUpdate{
    VALID, OCCUPIED
};

enum class BoardMarker{
    NOUGHT, CROSS, NONE
};

using InnerPos = std::array<BoardMarker, BoardLayout::NUM_CELLS>;
using OuterPos = std::array<InnerPos, BoardLayout::NUM_CELLS>;

class MarkerPositions{

   public:
   MarkerPositions();

   void updateMarkerAtPos(
        size_t outer, 
        size_t inner, 
        BoardMarker marker, 
        PosUpdate& update
    );

   const OuterPos& getMarkerPositions() const;
   void resetPositions();

   private:
   OuterPos pos = []{
        OuterPos o{};
        InnerPos i{};
        i.fill(BoardMarker::NONE);
        o.fill(i);
        return o;
   }();

   void checkPosition(size_t outer, size_t inner, PosUpdate& update);
};