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

enum class OuterCellState{
    ONGOING,
    NOUGHT_WON,
    CROSS_WON,
    DRAW
};

//TODO add some win condition struct 
class GameState{

    public:
    GameState(const MarkerPositions& positions);

    void checkInnerState(size_t outerCell);
    void checkOuterState();

    private:
    MarkerPositions markerPositions;
    std::array<OuterCellState, BoardLayout::NUM_CELLS> state;

    bool matchPosition(BoardMarker m1, BoardMarker m2) const;
    OuterCellState checkInnerDraw(const InnerPos& inner) const;
    OuterCellState checkInnerWinState(const InnerPos& inner) const;
    OuterCellState assignWinner(BoardMarker marker) const;

};

class Game{

    public:

    private:
        


};