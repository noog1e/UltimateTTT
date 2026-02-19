#pragma once

#include "PlayerManager.hpp"
#include "Board.hpp"
#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include "TurnManager.hpp"
#include "MoveProcessor.hpp"
#include "Renderer.hpp"
#include "UserInterface.hpp"
#include "InputController.hpp"

using MPOS = MarkerPositions;
using GS = GameState;
using TM = TurnManager;
using MPRO = MoveProcessor;
using PM = PlayerManager;
using UI = UserInterface;
using IC = InputController;

class GamePlay{

    public:
    GamePlay(
        const TM& t, 
        const MPRO& m, 
        const PM& pm,
        UI& ui,
        IC& g
    );

    void play();

    private:
    MPOS positions = MPOS(); 
    GS state = GS(); 
    TM turns; 
    MPRO moves; 
    Board board = Board();
    PM players;
    UI& display;
    IC& input;

    size_t selectInnerCell();
    PosUpdate applyPlayerMove(BoardMarker marker, size_t innerCell);

    void freeMove(size_t selectedCell);
    void selectOuterCell();

    bool outerCellOver(size_t outerCell);
    bool outerCellDraw(size_t outerCell);
    void outerCellEnding(size_t outerCell, std::string_view player);

    bool gameOver();
    void gameEnding();

    char convertMarkerToChar(BoardMarker marker);
    size_t cellSelection(BoardMarker pmarker);
};