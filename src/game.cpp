#include "Game.hpp"

Game::Game(        
        const MPOS& pos, 
        const GS& s, 
        const TM& t, 
        const MPRO& m, 
        const Board& b,
        const PM& pm,
        const Renderer& rd,
        const UI& u
    ) : positions(pos), state(s), turns(t), moves(m), board(b), players(pm), render(rd), ui(u){}