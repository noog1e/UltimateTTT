#include "PlayerManager.hpp"
#include <cassert>
#include <cstddef>
#include <string>

PlayerManager::PlayerManager(){}

NameUpdate PlayerManager::updateNames(const std::string& name1, const std::string& name2){

    if(name1 == name2) return NameUpdate::DUPLICATES;
    
    players[PlayerOne].name = name1;
    players[PlayerTwo].name = name2;

    return NameUpdate::VALID;
}

void PlayerManager::updateType(EntityType e, size_t playerSlot){

    assert(playerSlot < NUM_PLAYERS);

    players[playerSlot].type = e;
}

void PlayerManager::updateMarker(PlayerMarker marker, size_t playerSlot){

    assert(marker != PlayerMarker::NONE);

    size_t op = oppositePlayer(playerSlot);
    PlayerMarker om = oppositeMarker(marker);

    players[playerSlot].marker = marker;
    players[op].marker = om;
}

const Player& PlayerManager::getPlayer(size_t playerSlot) const{
    
    assert(playerSlot < NUM_PLAYERS);

    return players[playerSlot];
}

size_t PlayerManager::oppositePlayer(size_t playerSlot){
    return playerSlot == PlayerOne ? PlayerTwo : PlayerOne;
}

PlayerMarker PlayerManager::oppositeMarker(PlayerMarker marker){
    return marker == PlayerMarker::CROSS ? PlayerMarker::NOUGHT : PlayerMarker::CROSS;
}