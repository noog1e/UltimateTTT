#pragma once

#include <string>
#include <cstddef>

enum class PlayerMarker{
    NOUGHT, CROSS
};

struct Player{
    
    std::string name;
    //AI / Human flag
};

enum class Slot{
    ONE, TWO, COUNT
};

struct PlayerSlot{
    Player player;
    Slot slot;
    PlayerMarker marker;
};