#include "UserInterface.hpp"
#include "TextManager.hpp"
#include "Renderer.hpp"
#include <string>
#include <chrono>
#include <thread>
#include <windows.h>

UserInterface::UserInterface(Renderer& r, TextManager& t) : render(r), textM(t){
    #ifdef _WIN32
        enableVirtualTerminal();
    #endif
}

void UserInterface::inputArrows(){
    render.printLine(">> ", false);
}

void UserInterface::promptEntityTypes(size_t playerNum){
    std::string source = textM.getText(TextOptions::EntityTypes, std::to_string(playerNum), Placeholders::Id);
    render.printLine(source);
    inputArrows();
}

void UserInterface::promptPlayerNames(size_t playerNum){
    std::string source = textM.getText(TextOptions::PlayerNames, std::to_string(playerNum), Placeholders::Id);
    render.printLine(source);
    inputArrows();
}

void UserInterface::coinFlipping(){
    render.printLine(textM.getText(TextOptions::CoinFlip));
    delay(800);
}

void UserInterface::firstPlayer(std::string_view playerName){
    std::string source = textM.getText(TextOptions::FirstPlayer, playerName, Placeholders::Name);
    render.printLine(source);
    delay(1200);
}

void UserInterface::markerSelection(std::string_view playerName){
    std::string source = textM.getText(TextOptions::MarkerSelection, playerName, Placeholders::Name);    
    render.printLine(source);
    inputArrows();
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

void UserInterface::printBoard(const Board& board){

    const BoardView& bv = board.getBoard(); 

    for(size_t i = 0; i < board.getHeight(); i++){

        std::string_view row(bv[i].data(), bv[i].size());
        render.printLine(row);
    }

    render.printLine("");
}

void UserInterface::currentPlayerTurn(std::string_view playerName){
    std::string source = textM.getText(TextOptions::CurrentPlayer, playerName, Placeholders::Name);    
    render.printLine(source);
}

void UserInterface::currentOuterPosition(size_t outerCell){
    std::string source = textM.getText(TextOptions::CurrentOuter, std::to_string(outerCell), Placeholders::Cell);  
    render.printLine(source);
}

void UserInterface::playerSelectedCell(std::string_view playerName, size_t innerCell, size_t outerCell){

    std::string source = textM.getText(TextOptions::CellSelected);

    textM.replaceString(source, playerName, Placeholders::Name);
    textM.replaceString(source, std::to_string(innerCell), Placeholders::Cell);
    textM.replaceString(source, std::to_string(outerCell), Placeholders::Cell);
    
    render.printLine(source);
}

void UserInterface::freeMove(size_t outerCell, std::string_view playerName){
    std::string source = textM.getText(TextOptions::FreeMove);

    textM.replaceString(source, std::to_string(outerCell), Placeholders::Cell);
    textM.replaceString(source, playerName, Placeholders::Name);
    render.printLine(source);
}

void UserInterface::invalidOption(){
    render.printLine(textM.getText(TextOptions::InvalidOption));
    delay(800);
    clearLines(2);
    inputArrows();
}

void UserInterface::positionUnavailable(){
    render.printLine(textM.getText(TextOptions::PositionNA));
    delay(800);
    clearLines(2);
    inputArrows();
}

void UserInterface::localWin(std::string_view playerName, size_t outerCell){

    std::string source = textM.getText(TextOptions::LocalWin);

    textM.replaceString(source, playerName, Placeholders::Name);
    textM.replaceString(source, std::to_string(outerCell), Placeholders::Cell);

    render.printLine(source);
}

void UserInterface::localDraw(size_t outerCell){
    std::string source = textM.getText(TextOptions::LocalDraw, std::to_string(outerCell), Placeholders::Cell);
    render.printLine(source);
}

void UserInterface::gameWin(std::string_view playerName){
    std::string source = textM.getText(TextOptions::GameWin, playerName, Placeholders::Name);
    render.printLine(source);
}

void UserInterface::gameDraw(){
    render.printLine(textM.getText(TextOptions::GameDraw));
}

void UserInterface::cellPrompt(){
    render.printLine(textM.getText(TextOptions::CellPrompt));
    inputArrows();
}

void UserInterface::clear(){
    render.printLine("\033[H\033[J", false);
    std::cout << std::flush;
}

void UserInterface::clearLines(size_t count){

    for(size_t i=0; i < count; i++){
        render.printLine("\033[1A\033[2K", false);
        std::cout << std::flush;
    }
}

void UserInterface::enableVirtualTerminal(){
    HANDLE hOut =  GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;  
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void UserInterface::numberOuterCells(Board& board){
    
    size_t middleIn = 4;

    for(size_t i = 0; i < BoardLayout::NUM_CELLS; i++){

        char cellChar = (i+1) + '0';
        board.drawPositionUpdate(i, middleIn, cellChar);
    }
}