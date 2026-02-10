#include "TextManager.hpp"
#include "AssetLoader.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Replace String", "[text][replace]"){

    TextManager textm;

    SECTION("No game relevance"){
        std::string temp = "Stella @ Logan";

        textm.replaceString(temp, "and", "@");

        REQUIRE(temp == "Stella and Logan");
    }

    SECTION("Game relevance"){
        std::string temp = "{NAME} is the number {ID} prisoner in cell block {CELL}";

        textm.replaceString(temp, "Riddick", Placeholders::Name);
        textm.replaceString(temp, std::to_string(1), Placeholders::Id);
        textm.replaceString(temp, std::to_string(5), Placeholders::Cell);

        REQUIRE(temp == "Riddick is the number 1 prisoner in cell block 5");
    }
}

TEST_CASE("Load to Dictionary", "[text][dict]"){

    TextManager textm;
    AssetLoader assets;
    
    auto jopt = assets.loadJSON("F:/Programming/UltimateTTT/assets/ui_text.json");
    
    REQUIRE(jopt);

    json j = jopt.value();

    SECTION("Load Category: MENU"){

        REQUIRE(textm.loadJSONCategoryToDictionary(j, Categories::Menu));
    }

    SECTION("Load Category: GAME"){

        REQUIRE(textm.loadJSONCategoryToDictionary(j, Categories::Game));

    }
}