#pragma once

#include "TextManager.hpp"
#include "Renderer.hpp"
#include "InputController.hpp"
#include "AssetLoader.hpp"
#include "GameSetup.hpp"
#include "UserInterface.hpp"

class Game{

    public:
    Game();

    void startGame();

    private:
    Renderer render = Renderer();
    TextManager textM = TextManager();
    UserInterface ui;
    InputController input = InputController();
    AssetLoader loader = AssetLoader();

    void gameSetup();
    bool loadGamePlayAssets();
    void setEntityTypes(GameSetup& setup);
    size_t optionSelection(size_t numOptions);
    void setPlayerNames(GameSetup& setup);
    std::string enterPlayerName(size_t playerNum);

    void playGame();
};