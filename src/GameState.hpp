#pragma once

#include "BoardLayout.hpp"
#include "MarkerPositions.hpp"
#include <cstddef>
#include <array>

constexpr int NUM_CELL_COMBOS = 8;
constexpr int MAX_LINES_PER_CELL = 4;

using CellCombination = std::array<size_t, BoardLayout::CELLS_PER_AXIS>;
using WinConditions = std::array<CellCombination, NUM_CELL_COMBOS>;

constexpr WinConditions WIN_CONDITIONS = {{

    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},    //ROW Wins (0 - 2)
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},    //COL Wins (3 - 5)
    {0, 4, 8}, {2, 4, 6}                //Diagonal Wins (6 & 7)
}};

using CellWinConditionIndexes = std::array<size_t, MAX_LINES_PER_CELL>;

struct CellWinConditions{
    
    CellWinConditionIndexes cellLines;
    size_t count;
};

using CellWinLines = std::array<CellWinConditions, BoardLayout::NUM_CELLS>;

constexpr size_t ROW_0INDEX = 0;
constexpr size_t COL_0INDEX = 3;
constexpr size_t DIAG_0INDEX = 6;

constexpr CellWinLines CELL_WIN_LINES ={{

    /*0*/ {{ROW_0INDEX, COL_0INDEX, DIAG_0INDEX, 0}, MAX_LINES_PER_CELL - 1}, 
    /*1*/ {{ROW_0INDEX, COL_0INDEX + 1, 0, 0}, MAX_LINES_PER_CELL - 2}, 
    /*2*/ {{ROW_0INDEX, COL_0INDEX + 2, DIAG_0INDEX + 1, 0}, MAX_LINES_PER_CELL - 1},
    /*3*/ {{ROW_0INDEX + 1, COL_0INDEX, 0, 0}, MAX_LINES_PER_CELL - 2},
    /*4*/ {{ROW_0INDEX + 1, COL_0INDEX + 1, DIAG_0INDEX, DIAG_0INDEX + 1}, MAX_LINES_PER_CELL},
    /*5*/ {{ROW_0INDEX + 1, COL_0INDEX + 2, 0, 0}, MAX_LINES_PER_CELL - 2},
    /*6*/ {{ROW_0INDEX + 2, COL_0INDEX, DIAG_0INDEX + 1, 0}, MAX_LINES_PER_CELL - 1},
    /*7*/ {{ROW_0INDEX + 2, COL_0INDEX + 1, 0, 0}, MAX_LINES_PER_CELL - 2},
    /*8*/ {{ROW_0INDEX + 2, COL_0INDEX + 2, DIAG_0INDEX, 0}, MAX_LINES_PER_CELL - 1}
}};

enum class LineWinState{ 
    ALIVE, 
    NOUGHT_CAP, 
    CROSS_CAP, 
    BLOCKED
};

using LineWinStates = std::array<LineWinState, NUM_CELL_COMBOS>;

enum class MatchOutcome{
    ONGOING,
    NOUGHT_WON,
    CROSS_WON,
    DRAW
};

struct MatchEvaluationState{

    MatchOutcome matchOutcome = MatchOutcome::ONGOING;
    
    LineWinStates lineWinStates = []{
        LineWinStates s{};
        s.fill(LineWinState::ALIVE);
        return s;
    }();
};

struct MatchEvaluation{

    MatchEvaluationState overall;
    std::array<MatchEvaluationState, BoardLayout::NUM_CELLS> outer;
};

class GameState{

    public:
    GameState();

    void reset();

        /**
         * The idea is to import the marker that was changed at the specific outer cell, inner cell
         * location so that the object can decide whether that outer cell has ruled out all
         * possible moves, eventually deciding the overall state of the match.
         */
    void updateGameState(const InnerPos& ipos, size_t outerCell, size_t innerCell);

    const MatchEvaluation& getMatchEvaluation() const;

    private:
    MatchEvaluation eval;

    void resetOverallLWS();
    void resetOuterMS();
    void resetOuterLWS();

    void updateOverallMatchState();
    void updateOverallLineWinStates();
    void updateOuterMatchState(size_t outerCell);
    void updateOuterLineWinStates(const InnerPos& ipos, size_t outerCell, size_t innerCell);

    LineWinState updateCellLineWinState(const InnerPos& ipos, size_t lineIndex);
    LineWinState confirmBoardMarker(BoardMarker marker);
};