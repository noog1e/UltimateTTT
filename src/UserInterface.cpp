#include "UserInterface.hpp"
#include "TextManager.hpp"
#include "Renderer.hpp"
#include <string>
#include <chrono>
#include <thread>

UserInterface::UserInterface(Renderer& r, TextManager& t) : render(r), textM(t){}

void UserInterface::promptEntityTypes(size_t playerNum){
    std::string source = textM.getText(TextOptions::EntityTypes, std::to_string(playerNum), Placeholders::Id);
    render.printLine(source);
}

void UserInterface::promptPlayerNames(size_t playerNum){
    std::string source = textM.getText(TextOptions::PlayerNames, std::to_string(playerNum), Placeholders::Id);
    render.printLine(source);
}

void UserInterface::coinFlipping(){
    render.printLine(textM.getText(TextOptions::CoinFlip));
    delay(100);
}

void UserInterface::firstPlayer(std::string_view playerName){
    std::string source = textM.getText(TextOptions::FirstPlayer, playerName, Placeholders::Name);
    render.printLine(source);
}

void UserInterface::markerSelection(std::string_view playerName){
    std::string source = textM.getText(TextOptions::MarkerSelection, playerName, Placeholders::Name);    
    render.printLine(source);
}

void UserInterface::startingCell(std::string_view playerName){
    std::string source = textM.getText(TextOptions::StartingCell, playerName, Placeholders::Name);    
    render.printLine(source);
}

void UserInterface::confirmSetup(){
    render.printLine(textM.getText(TextOptions::SetupConfirmed));
}

void UserInterface::delay(int milliseconds){
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

UserInterface::UserInterface(Renderer& r, TextManager& t) : render(r), textM(t){}

void UserInterface::printBoard(const Board& board){

    const BoardView& bv = board.getBoard(); 

    for(size_t i = 0; i < board.getHeight(); i++){

        std::string_view row(bv[i].data(), bv[i].size());
        render.printLine(row);
    }

    render.printLine("");
}

void UserInterface::currentPlayerTurn(const Player& player){
    std::string source = textM.getText(TextOptions::CurrentPlayer, player.name, Placeholders::Id);    
    render.printLine(source);
}

void UserInterface::currentOuterPosition(size_t outerCell){
    std::string source = textM.getText(TextOptions::CurrentOuter, std::to_string(outerCell), Placeholders::Cell);  
    render.printLine(source);
}

void UserInterface::playerSelectedCell(const Player& player, size_t innerCell, size_t outerCell){

    std::string source = textM.getText(TextOptions::CellSelected);

    textM.replaceString(source, player.name, Placeholders::Name);
    textM.replaceString(source, std::to_string(innerCell), Placeholders::Cell);
    textM.replaceString(source, std::to_string(outerCell), Placeholders::Cell);
    
    render.printLine(source);
}

void UserInterface::freeMove(size_t outerCell, const Player& player){
    std::string source = textM.getText(TextOptions::FreeMove);

    textM.replaceString(source, std::to_string(outerCell), Placeholders::Cell);
    textM.replaceString(source, player.name, Placeholders::Name);
}

void UserInterface::invalidOption(size_t inputPos){
    render.printLine(textM.getText(TextOptions::InvalidOption));
}

void UserInterface::positionUnavailable(size_t inputPos){
    render.printLine(textM.getText(TextOptions::PositionNA));
}

void UserInterface::localWin(const Player& player, size_t outerCell){

    std::string source = textM.getText(TextOptions::LocalWin);

    textM.replaceString(source, player.name, Placeholders::Name);
    textM.replaceString(source, std::to_string(outerCell), Placeholders::Cell);

    render.printLine(source);
}

void UserInterface::localDraw(size_t outerCell){
    std::string source = textM.getText(TextOptions::LocalDraw, std::to_string(outerCell), Placeholders::Cell);
    render.printLine(source);
}

void UserInterface::gameWin(const Player& player){
    std::string source = textM.getText(TextOptions::GameWin, player.name, Placeholders::Name);
    render.printLine(source);
}

void UserInterface::gameDraw(){
    render.printLine(textM.getText(TextOptions::GameDraw));
}

void UserInterface::cellPrompt(){
    render.printLine(textM.getText(TextOptions::CellPrompt));
}