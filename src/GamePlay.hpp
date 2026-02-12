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
using UI = GameplayUI;
using GIC = GameInputController;

class GamePlay{

    public:
    GamePlay(
        const MPOS& pos, 
        const GS& s, 
        const TM& t, 
        const MPRO& m, 
        const Board& b,
        const PM& pm,
        const UI& ui,
        const GIC& g
    );

    void play();

    private:
    MPOS positions; 
    GS state; 
    TM turns; 
    MPRO moves; 
    Board board;
    PM players;
    UI display;
    GIC input;

    void selectInnerCell();
    PosUpdate applyPlayerMove(BoardMarker marker, size_t innerCell);

    void freeMove();
    void selectOuterCell();

    bool outerCellOver(size_t outerCell);
    void outerCellEnding(size_t outerCell);

    bool gameOver();
    void gameEnding();

    char convertMarkerToChar(BoardMarker marker);
};