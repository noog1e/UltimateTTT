#include "GamePlay.hpp"
#include "PlayerManager.hpp"
#include "Board.hpp"
#include "MarkerPositions.hpp"
#include "GameState.hpp"
#include "TurnManager.hpp"
#include "MoveProcessor.hpp"
#include "Renderer.hpp"
#include "UserInterface.hpp"
#include <optional>
#include <cassert>

GamePlay::GamePlay(        
        const MPOS& pos, 
        const GS& s, 
        const TM& t, 
        const MPRO& m, 
        const Board& b,
        const PM& pm,
        const UI& ui,
        const GIC& g
    ) : positions(pos), state(s), turns(t), moves(m), board(b), players(pm), display(ui), input(g){}

void GamePlay::play(){

    bool gameOver = false;

    while(!gameOver){

        display.printBoard(board);

        display.currentPlayerTurn(players.getPlayer(turns.currentPlayer()));
        display.currentOuterPosition(moves.getCurrentOuterCell());
        
        selectCell();



        
    }
}

void GamePlay::selectCell(){

    std::optional<size_t> inputopt;
    PosUpdate update;
    bool validated = false;
    size_t outerCell = moves.getCurrentOuterCell();
    BoardMarker pmarker = players.getPlayer(turns.currentPlayer()).marker;

    do{

        display.cellPrompt();
        inputopt = input.getInput();

        if(!inputopt){
            display.invalidMove(inputopt.value());
        } else{
            applyPlayerMove(pmarker, inputopt.value());
            if(update == PosUpdate::OCCUPIED){
                display.positionUnavailable(inputopt.value());
            }else{
                validated = true;
            }
        }

    }while(!validated);
}

PosUpdate GamePlay::applyPlayerMove(BoardMarker marker, size_t innerCell){

    assert(moves.getMoveConstraint() == MoveConstraint::FORCED_OUTER_CELL);

    PosUpdate update;

    positions.updateMarkerAtPos(moves.getCurrentOuterCell(), innerCell, marker, update);

    if(update == PosUpdate::VALID){
        const InnerPos& innerPos = positions.getMarkerPositions()[moves.getCurrentOuterCell()];
        state.updateGameState(innerPos, moves.getCurrentOuterCell(), innerCell);

        const MatchEvaluation& eval = state.getMatchEvaluation();
        moves.setCurrentOuterCell(innerCell, eval.outer);
    }

    return update;
}