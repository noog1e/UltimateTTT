#include "TurnManager.hpp"
#include <cstddef>

TurnManager::TurnManager(size_t startingPlayer, size_t numPlayers) :
    currentTurn(startingPlayer), playerCount(numPlayers){}

size_t TurnManager::currentPlayer() const{
    return currentTurn;
}

void TurnManager::nextPlayer(const TurnOutcome outcome){

    if(outcome == TurnOutcome::NORMAL){
        currentTurn = (currentTurn + 1) % playerCount;
    }
}

void TurnManager::setPlayerCount(size_t numPlayers){
    playerCount = numPlayers;
}

size_t TurnManager::getPlayerCount() const{
    return playerCount;
}