#pragma once

#include "PlayerManager.hpp"
#include "Board.hpp"
#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include "TurnManager.hpp"
#include "MoveProcessor.hpp"
#include "Renderer.hpp"
#include <string>
#include <array>
#include <cstddef>

using MPOS = MarkerPositions;
using GS = GameState;
using TM = TurnManager;
using MPRO = MoveProcessor;
using PM = PlayerManager;

class Game{

    public:
    Game(
        const MPOS& mpos, 
        const GS& gs, 
        const TM& tm, 
        const MPRO& mpro, 
        const Board& board,
        const PM& pm,
        const Renderer& ren
    );

    private:

        


};