#include "Game.hpp"
#include <catch2/catch_test_macros.hpp>
#include <windows.h>

TEST_CASE("Game Test", "[game][play]"){

    Game game;

    game.startGame();
}