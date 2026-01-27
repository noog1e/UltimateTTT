#pragma once

#include <array>
#include <string>

enum class EntityType{
    HUMAN, AI
};

enum class PlayerMarker{
    NOUGHT, CROSS
};

struct Entity{
    std::string name;
    EntityType type;
};

enum class Slot{
    ONE, TWO, COUNT
};

struct Player{
    Entity player;
    Slot slot;
    PlayerMarker marker;
};

constexpr int NUM_PLAYERS = 2;

class PlayerManager{

    public:
    PlayerManager();

    void addPlayer(const Player& newPlayer);
    const Player& getPlayer(Slot playerSlot);

    private:
    std::array<Player, NUM_PLAYERS> players;

};