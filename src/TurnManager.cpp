#include "TurnManager.hpp"

TurnManager::TurnManager(Slot startingPlayer) : currentTurn(startingPlayer){}

Slot TurnManager::currentPlayer() const{
    return currentTurn;
}

void TurnManager::nextPlayer(const TurnOutcome outcome){

    if(outcome == TurnOutcome::NORMAL){
        (static_cast<int>(currentTurn))
    }
}