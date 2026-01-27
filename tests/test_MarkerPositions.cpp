#include "TestingUtilities.hpp"
#include "MarkerPositions.hpp"
#include "BoardLayout.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Initialise Marker Positions object", "[marker][init]"){

    MarkerPositions positions;
    requireAllPositionsAs(positions, BoardMarker::NONE);
}

TEST_CASE("Update All Marker Positions", "[marker]"){

    MarkerPositions positions;

    SECTION("All positions with NOUGHT"){
        fillMarkerPositions(positions, BoardMarker::NOUGHT);
        requireAllPositionsAs(positions, BoardMarker::NOUGHT);
    }

    SECTION("All positions with CROSS"){
        fillMarkerPositions(positions, BoardMarker::CROSS);
        requireAllPositionsAs(positions, BoardMarker::CROSS);
    }

    SECTION("Reset positions"){
        positions.resetPositions();
        requireAllPositionsAs(positions, BoardMarker::NONE);
    }

}

TEST_CASE("Update Marker position states", "[marker][vacancy]"){

    MarkerPositions positions;
    PosUpdate update;

    size_t outer = 1;
    size_t inner = 1;

    SECTION("Position occupied; CROSS"){
        positions.updateMarkerAtPos(outer, inner, BoardMarker::CROSS, update);
        positions.updateMarkerAtPos(outer, inner, BoardMarker::NOUGHT, update);

        REQUIRE(update == PosUpdate::OCCUPIED);
    }

    SECTION("Position occupied; NOUGHT"){
        positions.updateMarkerAtPos(outer, inner, BoardMarker::NOUGHT, update);
        positions.updateMarkerAtPos(outer, inner, BoardMarker::CROSS, update);

        REQUIRE(update == PosUpdate::OCCUPIED);
    }

    SECTION("Reseting position to NONE"){
        positions.updateMarkerAtPos(outer, inner, BoardMarker::NOUGHT, update);
        positions.updateMarkerAtPos(outer, inner, BoardMarker::NONE, update);

        REQUIRE(update == PosUpdate::VALID);
    }
}