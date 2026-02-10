#include "AssetLoader.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Load JSON File", "[assets][load]"){

    AssetLoader assets;

    auto optionalJSON = assets.loadJSON("F:/Programming/UltimateTTT/assets/ui_text.json");

    REQUIRE(optionalJSON);
}