#pragma once

#include "Board.hpp"
#include "Renderer.hpp"
#include "PlayerManager.hpp"
#include <string>
#include <cstddef>

class GameplayUI{

    public:
    GameplayUI();

    void board(const Board& board, Renderer& render);
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