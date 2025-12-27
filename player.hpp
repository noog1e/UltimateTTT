#pragma once

#include <string>
#include <cstddef>

enum class PlayerSlot{
    ONE, TWO
};

enum class PlayerMarker{
    NOUGHT, CROSS
};

struct Player{
    PlayerSlot slot;
    std::string name;
    PlayerMarker marker;
};

class PlayerManager{

    public:

    private:

};