#pragma once
#include "PlayerManager.hpp"
#include "TurnManager.hpp"
#include "MoveProcessor.hpp"
#include <cstddef>

enum class SetupState{
    Entity, 
    Naming, 
    TurnManager, 
    Markers, 
    PlayerManager,
    StartingCell,
    Completed
};

struct SetupComponents{

};

class GameSetup{

    public:
    GameSetup();

    void entityTypes(EntityType p1, EntityType p2);
    NameUpdate playerNames(const std::string& p1, const std::string& p2);
    TurnManager turnManager();
    void playerMarkers(BoardMarker marker, size_t startingPlayer);
    PlayerManager extractPlayerManager();
    MoveProcessor startingCell(size_t cell);

    SetupState getSetupState();
    const Player& getStartingPlayer(size_t startingPlayer);

    private:
    SetupState setup = SetupState::Entity;
    PlayerManager pm;

    size_t coinToss();
};