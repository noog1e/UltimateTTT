#pragma once

#include "Board.hpp"
#include "Renderer.hpp"
#include "PlayerManager.hpp"
#include "TextManager.hpp"
#include <string>
#include <cstddef>

class GameSetupUI{

    public:
    GameSetupUI();

    void promptEntityTypes(int playerNum, Renderer& render, TextManager& textM);
    void promptPlayerNames(int playerNum, Renderer& render, TextManager& textM);
    void coinFlipping(Renderer& render, TextManager& textM);
    void firstPlayer(std::string playerName, Renderer& render, TextManager& textM);
    void markerSelection(std::string playerName, Renderer& render, TextManager& textM);
    void confirmSetup(Renderer& render, TextManager& textM);

    private:
    void delay(int milliseconds);
};

class GameplayUI{

    public:
    GameplayUI();

    void printBoard(const Board& board, Renderer& render, TextManager& textM);
    void currentPlayerTurn(const Player& player, Renderer& render, TextManager& textM);
    void currentOuterPosition(size_t outerCell, Renderer& render, TextManager& textM);
    void playerSelectedCell(const Player& player, size_t outerCell, size_t innerCell, Renderer& render, TextManager& textM);
    void invalidMove(size_t inputPos, Renderer& render, TextManager& textM);
    void positionUnavailable(size_t inputPos, Renderer& render, TextManager& textM);
    void localWin(const Player& player, size_t outerCell, Renderer& render, TextManager& textM);
    void localDraw(size_t outerCell, Renderer& render, TextManager& textM);
    void gameWin(const Player& player, Renderer& render, TextManager& textM);
    void gameDraw(Renderer& render, TextManager& textM);

    private:

};

class MainMenuUI{

    public:
    MainMenuUI();

    void homePage(Renderer& render, TextManager& textM);
    void howToPlay();

    private:

};