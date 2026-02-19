#pragma once

#include "TextManager.hpp"
#include "Renderer.hpp"
#include "InputController.hpp"
#include "AssetLoader.hpp"
#include "GameSetup.hpp"
#include "GamePlay.hpp"
#include "UserInterface.hpp"
#include <string>
#include <optional>

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

    std::optional<GamePlay> gameSetup();
    bool loadGamePlayAssets();
    void setEntityTypes(GameSetup& setup);
    size_t enterEntityType(size_t playerNum);
    void setPlayerNames(GameSetup& setup);
    std::string enterPlayerName(size_t playerNum);
    void setBoardMarker(GameSetup& setup, std::string_view playerName, size_t playerNum);
    MoveProcessor setStartingCell(GameSetup& setup, std::string_view playerName);
    size_t optionSelection(size_t numOptions);

    void playGame();
};