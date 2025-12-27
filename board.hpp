#pragma once

#include <array>
#include <cstddef>

static constexpr size_t INNER_GRID_CELLS = 9;
static constexpr size_t OUTER_GRID_CELLS = 9;

enum class BoardMarker{
    NOUGHT, CROSS, NONE
};

using Position = std::array<std::array<BoardMarker, INNER_GRID_CELLS>, OUTER_GRID_CELLS>;

class MarkerPosition{

    public:
    MarkerPosition();

    void updateMarkerAtPos(size_t outer, size_t inner);
    BoardMarker getMarkerAtPos(size_t outer, size_t inner);

    private:
    Position pos;

    void checkBounds(size_t outer, size_t inner);
    bool checkPosition(size_t outer, size_t inner);
};