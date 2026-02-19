#pragma once

#include "AssetLoader.hpp"
#include "json.hpp"
#include <map>
#include <string>
#include <filesystem>

using json = nlohmann::json;

namespace Placeholders{

    using namespace std::literals;

    static constexpr std::string_view Name = "{NAME}"sv;
    static constexpr std::string_view Id = "{ID}"sv;
    static constexpr std::string_view Cell = "{CELL}"sv;
}

namespace Categories{

    using namespace std::literals;
    static constexpr std::string_view Menu = "MENU"sv;
    static constexpr std::string_view Game = "GAME"sv;
}

enum class TextOptions{
    PlayGame,
    HowToPlayBtn,
    Exit,
    HowToPlayTxt,
    GameStart,
    EntityTypes,
    PlayerNames,
    CoinFlip,
    FirstPlayer,
    MarkerSelection,
    StartingCell,
    SetupConfirmed,
    CurrentPlayer,
    CurrentOuter,
    CellSelected,
    FreeMove,
    InvalidOption,
    PositionNA,
    LocalWin,
    LocalDraw,
    GameWin,
    GameDraw,
    CellPrompt,
    Unknown
};

NLOHMANN_JSON_SERIALIZE_ENUM(TextOptions, {
    {TextOptions::PlayGame,         "PlayGame"},
    {TextOptions::HowToPlayBtn,     "HowToPlayBtn"},
    {TextOptions::Exit,             "Exit"},
    {TextOptions::HowToPlayTxt,     "HowToPlayTxt"},
    {TextOptions::GameStart,        "GameStart"},
    {TextOptions::EntityTypes,      "EntityTypes"},
    {TextOptions::PlayerNames,      "PlayerNames"},
    {TextOptions::CoinFlip,         "CoinFlip"},
    {TextOptions::FirstPlayer,      "FirstPlayer"},
    {TextOptions::MarkerSelection,  "MarkerSelection"},
    {TextOptions::StartingCell,     "StartingCell"},
    {TextOptions::SetupConfirmed,   "SetupConfirmed"},
    {TextOptions::CurrentPlayer,    "CurrentPlayer"},
    {TextOptions::CurrentOuter,     "CurrentOuter"},
    {TextOptions::CellSelected,     "CellSelected"},
    {TextOptions::FreeMove,         "FreeMove"},
    {TextOptions::InvalidOption,    "InvalidOption"},
    {TextOptions::PositionNA,       "PositionNA"},
    {TextOptions::LocalWin,         "LocalWin"},
    {TextOptions::LocalDraw,        "LocalDraw"},
    {TextOptions::GameWin,          "GameWin"},
    {TextOptions::GameDraw,         "GameDraw"},
    {TextOptions::CellPrompt,      "CellPrompt"},
    {TextOptions::Unknown,           nullptr}
});

class TextManager{

    public:
    TextManager();
    
    void clearDictionary();
    
    bool loadJSONCategoryToDictionary(const json& jsonFile, std::string_view sub);
    void loadJSONToDictionary(const json& jsonFile);

    std::string getText(TextOptions key);
    std::string getText(TextOptions key, std::string_view replacement, std::string_view target);

    void replaceString(std::string& source, std::string_view replacement, std::string_view target);

    private:
    std::map<TextOptions, std::string> dict;
};