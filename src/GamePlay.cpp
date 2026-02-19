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
        const TM& t, 
        const MPRO& m, 
        const PM& pm,
        UI& ui,
        IC& g
    ) : turns(t), moves(m), players(pm), display(ui), input(g){}

void GamePlay::play(){

    size_t prevOuterCell = 0;
    size_t chosenOuterCell = 0;
    std::string_view prevPlayer;

    while(true){

        display.printBoard(board);

        if(gameOver()){
            gameEnding();
            break;
        }else if(outerCellOver(prevOuterCell)){
            outerCellEnding(prevOuterCell, prevPlayer);
        }

        if(moves.getMoveConstraint() == MoveConstraint::ANY){
            freeMove(chosenOuterCell + 1);
        }

        display.currentPlayerTurn(players.getPlayer(turns.currentPlayer()).name);
        display.currentOuterPosition(moves.getCurrentOuterCell() + 1);

        prevPlayer = players.getPlayer(turns.currentPlayer()).name;
        prevOuterCell = moves.getCurrentOuterCell();
        chosenOuterCell = selectInnerCell();

        turns.nextPlayer(TurnOutcome::NORMAL);
    }
}

size_t GamePlay::selectInnerCell(){

    std::optional<size_t> inputopt;
    PosUpdate update;
    bool validated = false;
    size_t outerCell = moves.getCurrentOuterCell();
    BoardMarker pmarker = players.getPlayer(turns.currentPlayer()).marker;

    do{

        display.cellPrompt();
        inputopt = input.readSizeInRange(1, BoardLayout::NUM_CELLS);

        if(!inputopt){
            display.invalidOption();
        } else{
            update = applyPlayerMove(pmarker, inputopt.value() - 1);
            if(update == PosUpdate::OCCUPIED){
                display.positionUnavailable();
            }else{

                if(outerCellOver(outerCell)){

                    if(outerCellDraw(outerCell)) pmarker = BoardMarker::NONE;
                    board.drawFillOuterCell(outerCell, convertMarkerToChar(pmarker));
                }else{
                    board.drawPositionUpdate(outerCell, inputopt.value() - 1, convertMarkerToChar(pmarker));
                }

                validated = true;
            }
        }

    }while(!validated);

    return inputopt.value() - 1;
}

bool GamePlay::outerCellOver(size_t outerCell){

    const MatchEvaluation& eval = state.getMatchEvaluation();

    return eval.outer[outerCell].matchOutcome != MatchOutcome::ONGOING;
}

bool GamePlay::outerCellDraw(size_t outerCell){
    const MatchEvaluation& eval = state.getMatchEvaluation();
    return eval.outer[outerCell].matchOutcome == MatchOutcome::DRAW;
}

void GamePlay::outerCellEnding(size_t outerCell, std::string_view player){
    
    const MatchEvaluation& eval = state.getMatchEvaluation();
 
    assert(eval.outer[outerCell].matchOutcome != MatchOutcome::ONGOING);

    if(outerCellDraw(outerCell)){
        display.localDraw(outerCell + 1);
    }else{
        display.localWin(player, outerCell + 1);
    }
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

void GamePlay::freeMove(size_t selectedCell){

    display.freeMove(selectedCell, players.getPlayer(turns.currentPlayer()).name);
    selectOuterCell();
}

void GamePlay::selectOuterCell(){
    std::optional<size_t> inputopt;
    bool validated = false;

    do{

        display.cellPrompt();
        inputopt = input.readSizeInRange(1, BoardLayout::NUM_CELLS);

        if(!inputopt){
            display.invalidOption();
        } else{

            const MatchEvaluation& eval = state.getMatchEvaluation();

            if(eval.outer[inputopt.value() - 1].matchOutcome == MatchOutcome::ONGOING){
                moves.setCurrentOuterCell(inputopt.value() - 1, eval.outer);
                validated = true;
            }else{
                display.positionUnavailable();
            }
        }
        
    }while(!validated);
}

bool GamePlay::gameOver(){
    return state.getMatchEvaluation().overall.matchOutcome != MatchOutcome::ONGOING;
}

void GamePlay::gameEnding(){
    
    MatchOutcome outcome = state.getMatchEvaluation().overall.matchOutcome;

    assert(outcome != MatchOutcome::ONGOING);

    if(outcome == MatchOutcome::DRAW){
        display.gameDraw();
    }else{
        display.gameWin(players.getPlayer(turns.currentPlayer()).name);
    }
}

char GamePlay::convertMarkerToChar(BoardMarker marker){

    if(marker == BoardMarker::NONE) return '?';

    return marker == BoardMarker::CROSS ? 'x' : 'o';
}