#include "PlayerManager.hpp"
#include "MarkerPositions.hpp"
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

void PlayerManager::updateMarker(BoardMarker marker, size_t playerSlot){

    assert(marker != BoardMarker::NONE);

    size_t op = oppositePlayer(playerSlot);
    BoardMarker om = oppositeMarker(marker);

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

BoardMarker PlayerManager::oppositeMarker(BoardMarker marker){
    return marker == BoardMarker::CROSS ? BoardMarker::NOUGHT : BoardMarker::CROSS;
}