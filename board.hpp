#pragma once

#include <array>
#include <cstddef>
#include <string>

static constexpr size_t NUM_DIM = 3;
static constexpr size_t NUM_CELLS = NUM_DIM * NUM_DIM;
static constexpr size_t NUM_X_LINES = NUM_DIM - 1;

enum class BoardMarker{
    NOUGHT, CROSS, NONE
};

enum class PosUpdate{
    VALID, CROSS_TAKEN, NOUGHT_TAKEN, OUTER_OOB, INNER_OOB 
};

using InnerGrid = std::array<BoardMarker, NUM_CELLS>;
using OuterGrid = std::array<InnerGrid, NUM_CELLS>;

class MarkerPositions{

    public:
    MarkerPositions();

    void updateMarkerAtPos(size_t outer, size_t inner, BoardMarker marker, PosUpdate& update);
    const OuterGrid& getMarkerPositions() const;

    private:
    OuterGrid pos;

    void checkBounds(size_t outer, size_t inner, PosUpdate& update);
    void checkPosition(size_t outer, size_t inner, PosUpdate& update);
};

class Board{

    public:
    Board();

    void draw(const OuterGrid& pos);
    void clear();
    
    private:
    void drawOuterRowDivider();
    void drawTopBottomGap();
    void drawSideGap();
    void drawInnerColumnDivider(bool hasRowLine);
    void drawInnerMarkerLine(const OuterGrid& pos, int outerXLayer, int innerXLayer);
    std::string drawPosChar(BoardMarker marker);
};


