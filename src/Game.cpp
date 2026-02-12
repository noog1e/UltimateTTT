#include "Game.hpp"
#include "GameSetup.hpp"
#include "InputController.hpp"
#include "AssetLoader.hpp"
#include "TextManager.hpp"
#include "Renderer.hpp"
#include "UserInterface.hpp"
#include <optional>
#include <filesystem>
#include <iostream>

const std::filesystem::path textAssetPathJSON = "../assets/ui_text.json";

Game::Game() : ui(render, textM){}

void Game::gameSetup(){

    if(loadGamePlayAssets()){
       
        GameSetup setup;
        UserInterface ui = UserInterface(render, textM);

        setEntityTypes(setup);
        setPlayerNames(setup);
        
        TurnManager tm = setup.turnManager();
    }
}

bool Game::loadGamePlayAssets(){

    textM.clearDictionary();

    auto jsonopt = loader.loadJSON(textAssetPathJSON);

    if(!jsonopt){
        std::cerr << "failed to loaded asset file: " << textAssetPathJSON << "\n";
        return false;
    }

    if(!textM.loadJSONCategoryToDictionary(*jsonopt, Categories::Game)){
        std::cerr << "error loading dictionary category: " << Categories::Game << "\n";
        return false;
    }

    return true;
}

void Game::setEntityTypes(GameSetup& setup){

    size_t numOptions = 2;

    ui.promptEntityTypes(1);
    size_t player1 = optionSelection(numOptions);

    ui.promptEntityTypes(2);
    size_t player2 = optionSelection(numOptions);

    setup.entityTypes(static_cast<EntityType>(player1 - 1), static_cast<EntityType>(player2 - 1));
}

void Game::setPlayerNames(GameSetup& setup){

    std::string player1 = enterPlayerName(1);
    
    NameUpdate u = NameUpdate::DUPLICATES;
    
    while(u == NameUpdate::DUPLICATES){
        std::string player2 = enterPlayerName(2);
        u = setup.playerNames(player1, player2);
    }
}

std::string Game::enterPlayerName(size_t playerNum){

    std::string name;

    ui.promptPlayerNames(playerNum);
    name = input.readString();
}

size_t Game::optionSelection(size_t numOptions){

    size_t inputval = 0;

    while(1){
        auto inputopt = input.readSizeInRange(1, numOptions);

        if(inputopt){
            inputval = *inputopt;
            break;
        }else{
            ui.invalidOption(*inputopt);
        }
    }

    return inputval;
}