#pragma once

#include "BoardLayout.hpp"
#include "MarkerPositions.hpp"
#include <cstddef>

enum class MatchState{
    ONGOING,
    NOUGHT_WON,
    CROSS_WON,
    DRAW
};

class GameState{

    public:
    GameState();

    void updateOuterState(const OuterPos& outerPos, size_t outerCell);
    void updateMatchState();

    MatchState getMatchState() const;

    private:
    std::array<MatchState, BoardLayout::NUM_CELLS> outerStates;
    MatchState matchState = MatchState::ONGOING;

    MatchState checkDraw(const InnerPos& inner) const;
    MatchState checkWinState(const InnerPos& inner) const;

    MatchState checkDraw() const;
    MatchState checkWinState() const;
    
    bool matchPosition(BoardMarker m1, BoardMarker m2) const;
    bool matchPosition(MatchState m1, MatchState m2) const;

    MatchState assignOuterWinner(BoardMarker marker) const;

};