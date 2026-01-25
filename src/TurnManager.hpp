#pragma once

#include "player.hpp"

enum class TurnOutcome{
    NORMAL, STAY, SKIP, ENDGAME
};

class TurnManager{

    public:
    TurnManager(Slot startingPlayer);

    Slot currentPlayer() const;
    void nextPlayer(const TurnOutcome outcome);

    private:
    Slot currentTurn;
};