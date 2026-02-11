#include "GamePlay.hpp"
#include "PlayerManager.hpp"
#include "Board.hpp"
#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include "TurnManager.hpp"
#include "MoveProcessor.hpp"
#include "Renderer.hpp"
#include "UserInterface.hpp"

GamePlay::GamePlay(        
        const MPOS& pos, 
        const GS& s, 
        const TM& t, 
        const MPRO& m, 
        const Board& b,
        const PM& pm
    ) : positions(pos), state(s), turns(t), moves(m), board(b), players(pm){}