#pragma once

#include <array>
#include <cstddef>

static constexpr size_t INNER_GRID_CELLS = 9;
static constexpr size_t OUTER_GRID_CELLS = 9;



enum class BoardMarker{
    NOUGHT, CROSS, NONE
};

enum class PosUpdate{
    VALID, CROSS_TAKEN, NOUGHT_TAKEN, OUTER_OOB, INNER_OOB 
};

using Position = std::array<std::array<BoardMarker, INNER_GRID_CELLS>, OUTER_GRID_CELLS>;

class MarkerPositions{

    public:
    MarkerPositions();

    void updateMarkerAtPos(size_t outer, size_t inner, BoardMarker marker, PosUpdate& update);
    const Position& getMarkerPositions() const;

    private:
    Position pos;

    void checkBounds(size_t outer, size_t inner, PosUpdate& update);
    void checkPosition(size_t outer, size_t inner, PosUpdate& update);
};

class Board{

    public:
    Board();

    void draw(const Position& pos);
    void clear();
    
    private:
    void drawOuterRowDivide();
    void drawOuterSpace();
    
};
