#pragma once

#include "player.hpp"
#include "board.hpp"
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



class Game{

    public:

    private:
        


};