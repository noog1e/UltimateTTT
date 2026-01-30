#pragma once

#include <array>
#include <string>
#include <cstddef>

enum class EntityType{
    HUMAN, AI, UNASSIGNED
};

enum class PlayerMarker{
    NOUGHT, CROSS, NONE
};

struct Player{
    std::string name = "UNASSIGNED";
    EntityType type = EntityType::UNASSIGNED;
    PlayerMarker marker = PlayerMarker::NONE;
};

constexpr int NUM_PLAYERS = 2;

class PlayerManager{

    public:
    PlayerManager();

    void updateName(const std::string& name, size_t playerSlot);
    void updateType(EntityType e, size_t playerSlot);
    void updateMarkers(PlayerMarker p1, PlayerMarker p2);
    const Player& getPlayer(size_t playerSlot) const;

    private:
    std::array<Player, NUM_PLAYERS> players = {};

};