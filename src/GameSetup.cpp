#include "GameSetup.hpp"
#include "PlayerManager.hpp"
#include "TurnManager.hpp"
#include <cstddef>
#include <cassert>
#include <random>

GameSetup::GameSetup(){}

void GameSetup::entityTypes(EntityType p1, EntityType p2){
    
    assert(setup == SetupState::Entity);

    pm.updateType(p1, 0);
    pm.updateType(p2, 1);

    setup = SetupState::Naming;
}

void GameSetup::playerNames(const std::string& p1, const std::string& p2){
    
    assert(setup == SetupState::Naming);
    
    pm.updateName(p1, 0);
    pm.updateName(p2, 1);
    
    setup = SetupState::TurnManager;
}

size_t GameSetup::coinToss(){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<size_t> dist (1, 2);

    return dist(gen);
}

TurnManager GameSetup::turnManager(){

    assert(setup == SetupState::TurnManager);

    size_t startingPlayer = coinToss();
    TurnManager tm(startingPlayer, NUM_PLAYERS);

    setup = SetupState::Markers;

    return tm;
}

void GameSetup::playerMarkers(PlayerMarker p1, PlayerMarker p2){

    assert(setup == SetupState::Markers);

    pm.updateMarkers(p1, p2);

    setup = SetupState::Completed;
}

PlayerManager GameSetup::extractPlayerManager(){

    assert(setup == SetupState::Completed);

    setup = SetupState::Extracted;

    return pm;
}