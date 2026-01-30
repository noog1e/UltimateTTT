#include "PlayerManager.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("Default init check", "[player][init]"){

    PlayerManager pm;

    for(size_t i = 0; i < NUM_PLAYERS; i++){

        const Player& p = pm.getPlayer(i);

        REQUIRE(p.name == "UNASSIGNED");
        REQUIRE(p.type == EntityType::UNASSIGNED);
        REQUIRE(p.marker == PlayerMarker::NONE);
    }
}