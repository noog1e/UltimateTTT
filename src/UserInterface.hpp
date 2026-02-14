#pragma once

#include "Board.hpp"
#include "Renderer.hpp"
#include "TextManager.hpp"
#include <string>
#include <cstddef>

class UserInterface{

    public:
    UserInterface(Renderer& r, TextManager& t);

    //Main Menu
    void homePage();
    void howToPlay();

    //GameSetup
    void promptEntityTypes(size_t playerNum);
    void promptPlayerNames(size_t playerNum);
    void coinFlipping();
    void firstPlayer(std::string_view playerName);
    void markerSelection(std::string_view playerName);
    void startingCell(std::string_view playerName);
    void confirmSetup();

    //GamePlay
    void printBoard(const Board& board);
    void currentPlayerTurn(std::string_view playerName);
    void currentOuterPosition(size_t outerCell);
    void playerSelectedCell(std::string_view playerName, size_t innerCell, size_t outerCell);
    void freeMove(size_t outerCell, std::string_view playerName);
    void invalidOption();
    void positionUnavailable();
    void localWin(std::string_view playerName, size_t outerCell);
    void localDraw(size_t outerCell);
    void gameWin(std::string_view playerName);
    void gameDraw();
    void cellPrompt();

    private:
    Renderer& render;
    TextManager& textM;

    void delay(int milliseconds);
    void inputArrows();
};