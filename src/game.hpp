#pragma once

#include "PlayerManager.hpp"
#include "Board.hpp"
#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include "TurnManager.hpp"
#include "MoveProcessor.hpp"
#include "Renderer.hpp"
#include "UserInterface.hpp"
#include <string>
#include <array>
#include <cstddef>

using MPOS = MarkerPositions;
using GS = GameState;
using TM = TurnManager;
using MPRO = MoveProcessor;
using PM = PlayerManager;
using UI = GameplayUI;

class Game{

    public:
    Game(
        const MPOS& pos, 
        const GS& s, 
        const TM& t, 
        const MPRO& m, 
        const Board& b,
        const PM& pm,
        const Renderer& rd,
        const UI& u
    );

    private:
    MPOS positions; 
    GS state; 
    TM turns; 
    MPRO moves; 
    Board board;
    PM players;
    Renderer render;
    UI ui;
};