#pragma once

#include "player.hpp"
#include <string>
#include <array>
#include <cstddef>

const size_t NUM_PLAYERS = 2; 

enum class Slot{
    ONE, TWO
};

class GameEvent{

    
};

//TODO add some win condition struct 
class GameState{

};

class Game{

    private:
        
    struct PlayerSlot{
        Player player;
        Slot slot;
        PlayerMarker marker;
    };

    struct PlayerState{
        PlayerSlot slot;
        bool isTurn;
        bool playsFirst;
        //Owned posiitons?
    };

};