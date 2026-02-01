#pragma once

#include "Board.hpp"
#include "Renderer.hpp"
#include "PlayerManager.hpp"
#include <string>
#include <cstddef>

class GameSetupUI{

    public:
    GameSetupUI();

    void promptEntityTypes(int playerNum, Renderer& render);
    void promptPlayerNames(int playerNum, Renderer& render);
    void coinFlipping(Renderer& render);
    void firstPlayer(std::string playerName, Renderer& render);
    void markerSelection(Renderer& render);
    void setupConfirmation(Renderer& render);

    private:
    void delay(int milliseconds);
};

class GameplayUI{

    public:
    GameplayUI();

    void printBoard(const Board& board, Renderer& render);
    void playerTurn(const Player& player, Renderer& render);
    void turnPosition(size_t outerCell, Renderer& render);
    void cellSelection(const Player& player, size_t outerCell, size_t innerCell, Renderer& render);
    void invalidMove(size_t inputPos, Renderer& render);
    void positionTaken(size_t inputPos, Renderer& render);
    void localWin(const Player& player, size_t outerCell, Renderer& render);
    void localDraw(size_t outerCell, Renderer& render);
    void gameWin(const Player& player, Renderer& render);
    void gameDraw(Renderer& render);

    private:

};

class MainMenuUI{


};