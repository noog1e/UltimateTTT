#pragma once

#include "player.hpp"
#include "board.hpp"
#include "WinConditions.hpp"
#include <string>
#include <array>
#include <cstddef>

const size_t NUM_PLAYERS = 2; 

enum class Slot{
    ONE, TWO
};

struct PlayerSlot{
    Player player;
    Slot slot;
    PlayerMarker marker;
};

struct PlayerState{
    PlayerSlot slot;
    bool isTurn;
    bool playsFirst;
};

class GameEvent{

    
};

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

class Game{

    public:

    private:
        


};