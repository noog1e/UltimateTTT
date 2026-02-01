#include "UserInterface.hpp"
#include <string>
#include <chrono>
#include <thread>

GameSetupUI::GameSetupUI(){}

void GameSetupUI::promptEntityTypes(int playerNum, Renderer& render){
    render.printLine("Player " + std::to_string(playerNum) + ": Human [1] / AI [2] ? ");
}

void GameSetupUI::promptPlayerNames(int playerNum, Renderer& render){
    render.printLine("Enter Player " +std::to_string(playerNum) + " name:");
}

void GameSetupUI::coinFlipping(Renderer& render){
    render.printLine("Flipping coin...");
    delay(100);
}

void GameSetupUI::firstPlayer(std::string playerName, Renderer& render){
    render.printLine(playerName + " goes first!");
}

void GameSetupUI::markerSelection(std::string playerName, Renderer& render){
    render.printLine(playerName + " choose your marker: CROSS [1] / NOUGHT [2] ?");
}

void GameSetupUI::setupConfirmation(Renderer& render){
    render.printLine("Let the game begin!");
}

void GameSetupUI::delay(int milliseconds){
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

GameplayUI::GameplayUI(){}

void GameplayUI::printBoard(const Board& board, Renderer& render){

    const BoardView& bv = board.getBoard(); 

    for(size_t i = 0; i < board.getHeight(); i++){

        std::string_view row(bv[i].data(), bv[i].size());
        render.printLine(row);
    }

}

void GameplayUI::playerTurn(const Player& player, Renderer& render){
    render.printLine("It is " + player.name + "'s turn");
}

void GameplayUI::turnPosition(size_t outerCell, Renderer& render){
    render.printLine("Currently in OUTER " + std::to_string(outerCell) + ". Select INNER:");
}

void GameplayUI::cellSelection(const Player& player, size_t outerCell, size_t innerCell, Renderer& render){
    render.printLine(player.name + " chose INNER " + std::to_string(innerCell) + " in OUTER " + std::to_string(outerCell));
}

void GameplayUI::invalidMove(size_t inputPos, Renderer& render){
    render.printLine("Invalid move, please try again!");
}

void GameplayUI::positionTaken(size_t inputPos, Renderer& render){
    render.printLine("Position taken, please try again!");
}

void GameplayUI::localWin(const Player& player, size_t outerCell, Renderer& render){
    render.printLine(player.name + " won OUTER " + std::to_string(outerCell));
}

void GameplayUI::localDraw(size_t outerCell, Renderer& render){
    render.printLine("OUTER " + std::to_string(outerCell) + " is a Draw");
}

void GameplayUI::gameWin(const Player& player, Renderer& render){
    render.printLine(player.name + " Wins!");
}

void GameplayUI::gameDraw(Renderer& render){
    render.printLine("Game Draw! Nobody wins!");
}