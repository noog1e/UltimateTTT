#include "GameSetup.hpp"
#include "PlayerManager.hpp"
#include "TurnManager.hpp"
#include <cstddef>
#include <cassert>
#include <random>

GameSetup::GameSetup(){}

void GameSetup::entityTypes(EntityType p1, EntityType p2){
    
    assert(setup == SetupState::Entity);
    assert(p1 != EntityType::UNASSIGNED);
    assert(p2 != EntityType::UNASSIGNED);

    pm.updateType(p1, 0);
    pm.updateType(p2, 1);

    setup = SetupState::Naming;
}

NameUpdate GameSetup::playerNames(const std::string& p1, const std::string& p2){
    
    assert(setup == SetupState::Naming);
    
    NameUpdate u = pm.updateNames(p1, p2);
    
    if(u == NameUpdate::VALID) setup = SetupState::TurnManager;

    return u;
}

size_t GameSetup::coinToss(){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<size_t> dist (0, 1);

    return dist(gen);
}

TurnManager GameSetup::turnManager(){

    assert(setup == SetupState::TurnManager);

    size_t startingPlayer = coinToss();
    TurnManager tm(startingPlayer, NUM_PLAYERS);

    setup = SetupState::Markers;

    return tm;
}

void GameSetup::playerMarkers(BoardMarker marker, size_t playerSlot){

    assert(setup == SetupState::Markers);
    assert(marker != BoardMarker::NONE);

    pm.updateMarker(marker, playerSlot);

    setup = SetupState::Completed;
}

PlayerManager GameSetup::extractPlayerManager(){

    assert(setup == SetupState::Completed);

    setup = SetupState::Extracted;

    return pm;
}

const SetupState GameSetup::getSetupState(){
    return setup;
}