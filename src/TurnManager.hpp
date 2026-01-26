#pragma once

#include <cstddef>

enum class TurnOutcome{
    NORMAL, STAY, SKIP, ENDGAME
};

class TurnManager{

    public:
    TurnManager(size_t startingPlayer, size_t numPlayers);

    size_t currentPlayer() const;
    void nextPlayer(const TurnOutcome outcome);

    void setPlayerCount(size_t numPlayers);
    size_t getPlayerCount() const;

    private:
    size_t currentTurn;
    size_t playerCount;
};