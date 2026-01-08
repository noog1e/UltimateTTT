#pragma once

#include "MarkerPositions.hpp"
#include "BoardLayout.hpp"
#include <cstddef>
#include <array>

constexpr int NUM_CELL_COMBOS = 8;

using CellCombination = std::array<size_t, BoardLayout::CELLS_PER_AXIS>;
using WinConditions = std::array<CellCombination, NUM_CELL_COMBOS>;

constexpr WinConditions WIN_CONDITIONS = {{

    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},    //Horizontal Wins
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},    //Vertical Wins
    {0, 4, 8}, {2, 4, 6}                //Diagonal Wins
}};

