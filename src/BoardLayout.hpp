#pragma once

#include <cstddef>

namespace BoardLayout{
    
    inline constexpr int CELLS_PER_AXIS = 3;
    inline constexpr int NUM_CELLS = 9;

    inline constexpr int GRID_DIVIDERS = CELLS_PER_AXIS - 1;

    inline constexpr int SUBGRID_MARGIN_WIDTH = 2;
    inline constexpr int SUBGRID_MARGIN_HEIGHT = 1;

    inline constexpr int INNER_CELL_WIDTH = 5;
    inline constexpr int INNER_CELL_HEIGHT = 3;
    inline constexpr int INNER_CELL_CENTRE_X = (INNER_CELL_WIDTH - 1) / 2;
    inline constexpr int INNER_CELL_CENTRE_Y = (INNER_CELL_HEIGHT - 1) / 2;

    inline constexpr int OUTER_CELL_WIDTH = 21;
    inline constexpr int OUTER_CELL_HEIGHT = 11;

    inline constexpr int U_HEIGHT = 35;    // Default Outer Height
    inline constexpr int U_WIDTH = 65;     // Default Outer Width

    inline constexpr int L_HEIGHT = 9;     // Default Inner Height
    inline constexpr int L_WIDTH = 17;     // Default Inner Width

    inline constexpr int U_GRID_THICKNESS = 1;   
    inline constexpr int L_GRID_THICKNESS = 1;
}

enum class PosUpdate{
    VALID, OCCUPIED
};