#include "PlayerManager.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>

TEST_CASE("Default init check", "[player][init]"){

    PlayerManager pm;

    for(size_t i = 0; i < NUM_PLAYERS; i++){

        const Player& p = pm.getPlayer(i);

        REQUIRE(p.name == "UNASSIGNED");
        REQUIRE(p.type == EntityType::UNASSIGNED);
        REQUIRE(p.marker == BoardMarker::NONE);
    }
}

TEST_CASE("Player Update Tests", "[player][update]"){

    PlayerManager pm;

    SECTION("Names"){

        NameUpdate nu;

        SECTION("Duplicates"){
            
            std::string n1 = "SAME";
            std::string n2 = "SAME";

            nu = pm.updateNames(n1, n2);

            REQUIRE(nu == NameUpdate::DUPLICATES);
        }

        SECTION("Different"){
            
            std::string n1 = "SAME";
            std::string n2 = "DIFFERENT";

            nu = pm.updateNames(n1, n2);

            REQUIRE(nu == NameUpdate::VALID);
        }
        
    }

    SECTION("Type"){

        pm.updateType(EntityType::HUMAN, PlayerOne);
        REQUIRE(pm.getPlayer(PlayerOne).type == EntityType::HUMAN);
        
        pm.updateType(EntityType::AI, PlayerTwo);
        REQUIRE(pm.getPlayer(PlayerTwo).type == EntityType::AI);
    }

    SECTION("Marker"){
        
        pm.updateMarker(BoardMarker::CROSS, PlayerOne);

        REQUIRE(pm.getPlayer(PlayerOne).marker == BoardMarker::CROSS);
        REQUIRE(pm.getPlayer(PlayerTwo).marker == BoardMarker::NOUGHT);
    }
}