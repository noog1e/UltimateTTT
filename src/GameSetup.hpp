#pragma once
#include "PlayerManager.hpp"
#include "TurnManager.hpp"
#include <cstddef>

enum class SetupState{
    Entity, Naming, TurnManager, Markers, Completed, Extracted
};

class GameSetup{

    public:
    GameSetup();

    void entityTypes(EntityType p1, EntityType p2);
    NameUpdate playerNames(const std::string& p1, const std::string& p2);
    TurnManager turnManager();
    void playerMarkers(PlayerMarker marker, size_t playerSlot);
    PlayerManager extractPlayerManager();

    const SetupState getSetupState();

    private:
    SetupState setup;
    PlayerManager pm;

    size_t coinToss();
};