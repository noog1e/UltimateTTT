#include "UserInterface.hpp"
#include <string>
#include <chrono>
#include <thread>

GameSetupUI::GameSetupUI(){}

void GameSetupUI::promptEntityTypes(int playerNum, Renderer& render, TextManager& textM){

    
    render.printLine("Player " + std::to_string(playerNum) + ": Human [1] / AI [2] ? ");
}

void GameSetupUI::promptPlayerNames(int playerNum, Renderer& render, TextManager& textM){
    render.printLine("Enter Player " +std::to_string(playerNum) + " name:");
}

void GameSetupUI::coinFlipping(Renderer& render, TextManager& textM){
    render.printLine("Flipping coin...");
    delay(100);
}

void GameSetupUI::firstPlayer(std::string playerName, Renderer& render, TextManager& textM){
    render.printLine(playerName + " goes first!");
}

void GameSetupUI::markerSelection(std::string playerName, Renderer& render, TextManager& textM){
    render.printLine(playerName + " choose your marker: CROSS [1] / NOUGHT [2] ?");
}

void GameSetupUI::confirmSetup(Renderer& render, TextManager& textM){
    render.printLine("Let the game begin!");
}

void GameSetupUI::delay(int milliseconds){
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

GameplayUI::GameplayUI(){}

void GameplayUI::printBoard(const Board& board, Renderer& render, TextManager& textM){

    const BoardView& bv = board.getBoard(); 

    for(size_t i = 0; i < board.getHeight(); i++){

        std::string_view row(bv[i].data(), bv[i].size());
        render.printLine(row);
    }

}

void GameplayUI::currentPlayerTurn(const Player& player, Renderer& render, TextManager& textM){
    render.printLine("It is " + player.name + "'s turn");
}

void GameplayUI::currentOuterPosition(size_t outerCell, Renderer& render, TextManager& textM){
    render.printLine("Currently in OUTER " + std::to_string(outerCell) + ". Select INNER:");
}

void GameplayUI::playerSelectedCell(const Player& player, size_t outerCell, size_t innerCell, Renderer& render, TextManager& textM){
    render.printLine(player.name + " chose INNER " + std::to_string(innerCell) + " in OUTER " + std::to_string(outerCell));
}

void GameplayUI::invalidMove(size_t inputPos, Renderer& render, TextManager& textM){
    render.printLine("Invalid move, please try again!");
}

void GameplayUI::positionUnavailable(size_t inputPos, Renderer& render, TextManager& textM){
    render.printLine("Position taken, please try again!");
}

void GameplayUI::localWin(const Player& player, size_t outerCell, Renderer& render, TextManager& textM){
    render.printLine(player.name + " won OUTER " + std::to_string(outerCell));
}

void GameplayUI::localDraw(size_t outerCell, Renderer& render, TextManager& textM){
    render.printLine("OUTER " + std::to_string(outerCell) + " is a Draw");
}

void GameplayUI::gameWin(const Player& player, Renderer& render, TextManager& textM){
    render.printLine(player.name + " Wins!");
}

void GameplayUI::gameDraw(Renderer& render, TextManager& textM){
    render.printLine("Game Draw! Nobody wins!");
}