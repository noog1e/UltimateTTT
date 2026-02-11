#pragma once

#include "Board.hpp"
#include "Renderer.hpp"
#include "PlayerManager.hpp"
#include "TextManager.hpp"
#include <string>
#include <cstddef>

class GameSetupUI{

    public:
    GameSetupUI(Renderer& r, TextManager& t);

    void promptEntityTypes(int playerNum);
    void promptPlayerNames(int playerNum);
    void coinFlipping();
    void firstPlayer(std::string_view playerName);
    void markerSelection(std::string_view playerName);
    void confirmSetup();

    private:
    Renderer& render;
    TextManager& textM;

    void delay(int milliseconds);
};

class GameplayUI{

    public:
    GameplayUI(Renderer& r, TextManager& t);

    void printBoard(const Board& board);
    void currentPlayerTurn(const Player& player);
    void currentOuterPosition(size_t outerCell);
    void playerSelectedCell(const Player& player, size_t innerCell, size_t outerCell);
    void invalidMove(size_t inputPos);
    void positionUnavailable(size_t inputPos);
    void localWin(const Player& player, size_t outerCell);
    void localDraw(size_t outerCell);
    void gameWin(const Player& player);
    void gameDraw();
    void cellPrompt();

    private:
    Renderer& render;
    TextManager& textM;

};

class MainMenuUI{

    public:
    MainMenuUI();

    void homePage(Renderer& render, TextManager& textM);
    void howToPlay();

    private:

};