#include "GameSetup.hpp"
#include "PlayerManager.hpp"
#include "TurnManager.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("GameSetup Init", "[setup][init]"){

    GameSetup setup;
    REQUIRE(setup.getSetupState() == SetupState::Entity);
}

TEST_CASE("Full Run Through", "[setup][run]"){

    GameSetup setup;

    setup.entityTypes(EntityType::HUMAN, EntityType::AI);
    REQUIRE(setup.getSetupState() == SetupState::Naming);
    
    NameUpdate u = setup.playerNames("Georgy", "Bill");
    REQUIRE(u == NameUpdate::VALID);
    REQUIRE(setup.getSetupState() == SetupState::TurnManager);

    TurnManager tm = setup.turnManager();
    REQUIRE(tm.getPlayerCount() == NUM_PLAYERS);
    REQUIRE((tm.currentPlayer() == PlayerOne || tm.currentPlayer() == PlayerTwo));
    REQUIRE(setup.getSetupState() == SetupState::Markers);

    setup.playerMarkers(BoardMarker::NOUGHT, tm.currentPlayer());
    REQUIRE(setup.getSetupState() == SetupState::Completed);
    
    PlayerManager pm = setup.extractPlayerManager();
    REQUIRE(setup.getSetupState() == SetupState::Extracted);

    REQUIRE((pm.getPlayer(PlayerOne).marker == BoardMarker::CROSS || 
             pm.getPlayer(PlayerOne).marker == BoardMarker::NOUGHT));
    REQUIRE((pm.getPlayer(PlayerTwo).marker == BoardMarker::CROSS || 
             pm.getPlayer(PlayerTwo).marker == BoardMarker::NOUGHT));

}