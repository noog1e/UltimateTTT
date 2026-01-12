#pragma once

#include "BoardLayout.hpp"
#include "MarkerPositions.hpp"
#include <cstddef>
#include <vector>
#include <array>

constexpr int NUM_CELL_COMBOS = 8;
constexpr int MAX_LINES = 4;

using CellCombination = std::array<size_t, BoardLayout::CELLS_PER_AXIS>;
using WinConditions = std::array<CellCombination, NUM_CELL_COMBOS>;

constexpr WinConditions WIN_CONDITIONS = {{

    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},    //Horizontal Wins
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},    //Vertical Wins
    {0, 4, 8}, {2, 4, 6}                //Diagonal Wins
}};

enum class MatchState{
    ONGOING,
    NOUGHT_WON,
    CROSS_WON,
    DRAW
};

enum class LineState{
    ALIVE, BLOCKED
};

using OuterStates = std::array<MatchState, BoardLayout::NUM_CELLS>; 
using LineStates = std::array<std::array<LineState, NUM_CELL_COMBOS>, BoardLayout::NUM_CELLS>;
using LineIndexes = std::vector<size_t>;

class GameState{

    public:
    GameState();

    void updateOuterState(const OuterPos& outerPos, size_t outerCellUpdated, size_t innerCellUpdated);
    void updateMatchState();

    MatchState getMatchState() const;
    const OuterStates& getOuterStates() const;

    private:
    MatchState matchState = MatchState::ONGOING;
    OuterStates outerStates;
    LineStates lineStates;

    void findLineStateIndexes(LineIndexes& lineIndexes, size_t outerCellUpdated, size_t innerCellUpdated);
    void updateLineState(size_t outerCellUpdated, size_t innerCellUpdated);

    MatchState checkDrawState(const InnerPos& inner) const;
    MatchState checkWinState(const InnerPos& inner) const;

    MatchState checkDrawState() const;
    MatchState checkWinState() const;
    
    bool matchPosition(BoardMarker m1, BoardMarker m2) const;
    bool matchPosition(MatchState s1, MatchState s2) const;
    bool boardMarkersNone(BoardMarker m1, BoardMarker m2) const;
    bool matchStatesOngoing(MatchState s1, MatchState s2) const;

    MatchState assignOuterWinner(BoardMarker marker) const;

};