#pragma once

#include "TextManager.hpp"
#include "Renderer.hpp"

class Game{

    public:
    Game();

    void startGame();

    private:
    TextManager textM = TextManager();
    Renderer render = Renderer();

    void gameSetup();
    void playGame();
};