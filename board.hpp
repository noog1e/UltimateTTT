#pragma once

#include <array>
#include <cstddef>
#include <string>

static constexpr size_t NUM_DIM = 3;
static constexpr size_t NUM_CELLS = NUM_DIM * NUM_DIM;

static constexpr size_t U_HEIGHT = 35;
static constexpr size_t U_WIDTH = 65;
static constexpr size_t L_HEIGHT = 17;
static constexpr size_t L_WIDTH = 9;
using board2DArray = std::array<std::array<char, U_WIDTH>, U_HEIGHT>;

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
    //Board(size_t )

    void clear();

    const board2DArray& getBoard() const;
    size_t getHeight() const;
    size_t getWidth() const;

    
    private:
    board2DArray board;
    size_t height = U_HEIGHT;
    size_t width = U_WIDTH;
    
    std::string drawPosChar(BoardMarker marker);
};


