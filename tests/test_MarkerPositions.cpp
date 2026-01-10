#include <catch2/catch_test_macros.hpp>
#include "MarkerPositions.hpp"
#include "BoardLayout.hpp"

void fillMarkerPositions(MarkerPositions& positions, BoardMarker marker){

    PosUpdate update;

    for(size_t i=0; i < BoardLayout::NUM_CELLS; i++){

        for(size_t j=0; j < BoardLayout::NUM_CELLS; j++){

            positions.updateMarkerAtPos(i+1, j+1, marker, update);
        }
    }
}

void requireAllPositionsAs(MarkerPositions& positions, BoardMarker marker){

    const OuterPos& outPos = positions.getMarkerPositions();

    for(size_t i=0; i < BoardLayout::NUM_CELLS; i++){

        const InnerPos& inPos = outPos[i];

        for(size_t j=0; j < BoardLayout::NUM_CELLS; j++){

            REQUIRE(inPos[j] == marker);
        }
    }

}

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

TEST_CASE("Update Marker Bounds Checking", "[marker][bounds]"){
    
    MarkerPositions positions;
    PosUpdate update;

    SECTION("Update Outer; buffer overflow check"){
        
        size_t outer = 10;
        size_t inner = 1;
        positions.updateMarkerAtPos(outer, inner, BoardMarker::CROSS, update);

        REQUIRE(update == PosUpdate::OUT_OF_BOUNDS);
    }

    SECTION("Update Outer; buffer underflow check"){
        
        size_t outer = 0;
        size_t inner = 1;
        positions.updateMarkerAtPos(outer, inner, BoardMarker::CROSS, update);

        REQUIRE(update == PosUpdate::OUT_OF_BOUNDS);
    }

    SECTION("Update Inner; buffer overflow check"){
        
        size_t outer = 1;
        size_t inner = 10;
        positions.updateMarkerAtPos(outer, inner, BoardMarker::CROSS, update);

        REQUIRE(update == PosUpdate::OUT_OF_BOUNDS);
    }

    SECTION("Update Inner; buffer underflow check"){
        
        size_t outer = 1;
        size_t inner = 0;
        positions.updateMarkerAtPos(outer, inner, BoardMarker::CROSS, update);

        REQUIRE(update == PosUpdate::OUT_OF_BOUNDS);
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