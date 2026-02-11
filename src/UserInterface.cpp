#include "UserInterface.hpp"
#include "TextManager.hpp"
#include "Renderer.hpp"
#include <string>
#include <chrono>
#include <thread>

GameSetupUI::GameSetupUI(Renderer& r, TextManager& t) : render(r), textM(t){}

void GameSetupUI::promptEntityTypes(int playerNum){
    std::string source = textM.getText(TextOptions::EntityTypes, std::to_string(playerNum), Placeholders::Id);
    render.printLine(source);
}

void GameSetupUI::promptPlayerNames(int playerNum){
    std::string source = textM.getText(TextOptions::PlayerNames, std::to_string(playerNum), Placeholders::Id);
    render.printLine(source);
}

void GameSetupUI::coinFlipping(){
    render.printLine(textM.getText(TextOptions::CoinFlip));
    delay(100);
}

void GameSetupUI::firstPlayer(std::string_view playerName){
    std::string source = textM.getText(TextOptions::FirstPlayer, playerName, Placeholders::Id);
    render.printLine(source);
}

void GameSetupUI::markerSelection(std::string_view playerName){
    std::string source = textM.getText(TextOptions::MarkerSelection, playerName, Placeholders::Id);    
    render.printLine(source);
}

void GameSetupUI::confirmSetup(){
    render.printLine(textM.getText(TextOptions::SetupConfirmed));
}

void GameSetupUI::delay(int milliseconds){
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

GameplayUI::GameplayUI(Renderer& r, TextManager& t) : render(r), textM(t){}

void GameplayUI::printBoard(const Board& board){

    const BoardView& bv = board.getBoard(); 

    for(size_t i = 0; i < board.getHeight(); i++){

        std::string_view row(bv[i].data(), bv[i].size());
        render.printLine(row);
    }

    render.printLine("");
}

void GameplayUI::currentPlayerTurn(const Player& player){
    std::string source = textM.getText(TextOptions::CurrentPlayer, player.name, Placeholders::Id);    
    render.printLine(source);
}

void GameplayUI::currentOuterPosition(size_t outerCell){
    std::string source = textM.getText(TextOptions::CurrentOuter, std::to_string(outerCell), Placeholders::Cell);  
    render.printLine(source);
}

void GameplayUI::playerSelectedCell(const Player& player, size_t innerCell, size_t outerCell){

    std::string source = textM.getText(TextOptions::CellSelected);

    textM.replaceString(source, player.name, Placeholders::Name);
    textM.replaceString(source, std::to_string(innerCell), Placeholders::Cell);
    textM.replaceString(source, std::to_string(outerCell), Placeholders::Cell);
    
    render.printLine(source);
}

void GameplayUI::invalidMove(size_t inputPos){
    render.printLine(textM.getText(TextOptions::InvalidMove));
}

void GameplayUI::positionUnavailable(size_t inputPos){
    render.printLine(textM.getText(TextOptions::PositionNA));
}

void GameplayUI::localWin(const Player& player, size_t outerCell){

    std::string source = textM.getText(TextOptions::LocalWin);

    textM.replaceString(source, player.name, Placeholders::Name);
    textM.replaceString(source, std::to_string(outerCell), Placeholders::Cell);

    render.printLine(source);
}

void GameplayUI::localDraw(size_t outerCell){
    std::string source = textM.getText(TextOptions::LocalDraw, std::to_string(outerCell), Placeholders::Cell);
    render.printLine(source);
}

void GameplayUI::gameWin(const Player& player){
    std::string source = textM.getText(TextOptions::GameWin, player.name, Placeholders::Name);
    render.printLine(source);
}

void GameplayUI::gameDraw(){
    render.printLine(textM.getText(TextOptions::GameDraw));
}

void GameplayUI::cellPrompt(){
    render.printLine(textM.getText(TextOptions::CellPrompt));
}