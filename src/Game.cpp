#include "Game.hpp"
#include "GameSetup.hpp"
#include "GamePlay.hpp"
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

void Game::startGame(){

    ui.clear();
    auto gameopt = gameSetup();

    if(gameopt){
        gameopt.value().play();
    }
}

std::optional<GamePlay> Game::gameSetup(){

    if(!loadGamePlayAssets()){
        std::cerr << "Assets not loaded properly\n";
        return std::nullopt;
    }
       
    GameSetup setup;

    setEntityTypes(setup);
    setPlayerNames(setup);
    
    ui.coinFlipping();
    
    TurnManager tm = setup.turnManager();
    Player startingPlayer = setup.getStartingPlayer(tm.currentPlayer());

    ui.firstPlayer(startingPlayer.name);
    ui.clear();
    
    setBoardMarker(setup, startingPlayer.name, tm.currentPlayer());
    PlayerManager pm = setup.extractPlayerManager();
    MoveProcessor mv = setStartingCell(setup, startingPlayer.name);

    if(setup.getSetupState() != SetupState::Completed)
        return std::nullopt;
        
    GamePlay gameplay(tm, mv, pm, ui, input);

    return gameplay;
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

    size_t player1 = enterEntityType(1);
    ui.clear();
    size_t player2 = enterEntityType(2);
    ui.clear();

    setup.entityTypes(static_cast<EntityType>(player1 - 1), static_cast<EntityType>(player2 - 1));
}

size_t Game::enterEntityType(size_t playerNum){
    size_t numOptions = 2;
    ui.promptEntityTypes(playerNum);
    return optionSelection(numOptions);
}

void Game::setPlayerNames(GameSetup& setup){

    std::string player1 = enterPlayerName(1);
    ui.clear();
    
    NameUpdate u = NameUpdate::DUPLICATES;
    
    while(u == NameUpdate::DUPLICATES){
        std::string player2 = enterPlayerName(2);
        u = setup.playerNames(player1, player2);
    }

    ui.clear();
}

std::string Game::enterPlayerName(size_t playerNum){

    std::string name;

    ui.promptPlayerNames(playerNum);
    name = input.readString();

    return name;
}

void Game::setBoardMarker(GameSetup& setup, std::string_view playerName, size_t playerNum){

    size_t numOptions = 2;

    ui.markerSelection(playerName);
    size_t selection = optionSelection(numOptions);

    setup.playerMarkers(static_cast<BoardMarker>(selection-1), playerNum);

    ui.clear();
}

MoveProcessor Game::setStartingCell(GameSetup& setup, std::string_view playerName){

    Board tempBoard;
    ui.numberOuterCells(tempBoard);

    ui.printBoard(tempBoard);
    ui.startingCell(playerName);
    ui.cellPrompt();

    size_t inputval = 0;

    while(1){
        auto inputopt = input.readSizeInRange(1, BoardLayout::NUM_CELLS);
        
        if(inputopt){
            inputval = *inputopt;
            break;
        }else{
            ui.invalidOption();
        }
    }    

    ui.clear();

    return setup.startingCell(inputval - 1);;
}

size_t Game::optionSelection(size_t numOptions){

    size_t inputval = 0;

    while(1){
        auto inputopt = input.readSizeInRange(1, numOptions);

        if(inputopt){
            inputval = *inputopt;
            break;
        }else{
            ui.invalidOption();
        }
    }

    return inputval;
}