#include "InputController.hpp"
#include "BoardLayout.hpp"
#include <catch2/catch_test_macros.hpp>
#include <optional>

TEST_CASE("User Input", "[input][valid]"){

    GameInputController gic;

    std::optional<size_t> index = gic.getInput();

    REQUIRE(index.has_value());
    REQUIRE(index.value() < BoardLayout::NUM_CELLS);
}