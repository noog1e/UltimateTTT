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

constexpr size_t NUM_PLAYERS = 2;
constexpr size_t PlayerOne = 0;
constexpr size_t PlayerTwo = 1;

enum class NameUpdate{
    VALID, DUPLICATES
};

class PlayerManager{

    public:
    PlayerManager();

    NameUpdate updateNames(const std::string& name1, const std::string& name2);
    void updateType(EntityType e, size_t playerSlot);
    void updateMarker(PlayerMarker marker, size_t playerSlot);
    const Player& getPlayer(size_t playerSlot) const;

    private:
    std::array<Player, NUM_PLAYERS> players = {};

    size_t oppositePlayer(size_t playerSlot);
    PlayerMarker oppositeMarker(PlayerMarker marker);

};