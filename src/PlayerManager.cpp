#include "PlayerManager.hpp"
#include <cassert>
#include <cstddef>
#include <string>

PlayerManager::PlayerManager(){}

void PlayerManager::updateName(const std::string& name, size_t playerSlot){

    assert(playerSlot < NUM_PLAYERS);

    players[playerSlot].name = name;
}

void PlayerManager::updateType(EntityType e, size_t playerSlot){

    assert(playerSlot < NUM_PLAYERS);

    players[playerSlot].type = e;
}

void PlayerManager::updateMarkers(PlayerMarker p1, PlayerMarker p2){

    assert(p1 == PlayerMarker::NONE);
    assert(p2 == PlayerMarker::NONE);
    assert(p1 == p2);

    players[0].marker = p1;
    players[1].marker = p2;
}

const Player& PlayerManager::getPlayer(size_t playerSlot) const{
    
    assert(playerSlot < NUM_PLAYERS);

    return players[playerSlot];
}