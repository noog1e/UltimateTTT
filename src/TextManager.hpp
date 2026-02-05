#pragma once

#include "LoadAssets.hpp"
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

enum class TextOptions{
    PlayGame,
    HowToPlayBtn,
    Exit,
    HowToPlayTxt,
    EntityTypes,
    PlayerNames,
    CoinFlip,
    FirstPlayer,
    MarkerSelection,
    SetupConfirmed,
    CurrentPlayer,
    CurrentOuter,
    CellSelected,
    FreeMove,
    InvalidMove,
    PositionNA,
    LocalWin,
    LocalDraw,
    GameWin,
    GameDraw,
    Unknown
};

NLOHMANN_JSON_SERIALIZE_ENUM(TextOptions, {
    {PlayGame, "PlayGame"},
    {HowToPlayBtn, "HowToPlayBtn"},
    {Exit, "Exit"},
    {HowToPlayTxt, "HowToPlayTxt"},
    {EntityTypes, "EntityTypes"},
    {PlayerNames, "PlayerNames"},
    {CoinFlip, "CoinFlip"},
    {FirstPlayer, "FirstPlayer"},
    {MarkerSelection, "MarkerSelection"},
    {SetupConfirmed, "SetupConfirmed"},
    {CurrentPlayer, "CurrentPlayer"},
    {CurrentOuter, "CurrentOuter"},
    {CellSelected, "CellSelected"},
    {FreeMove, "FreeMove"},
    {InvalidMove, "InvalidMove"},
    {PositionNA, "PositionNA"},
    {LocalWin, "LocalWin"},
    {LocalDraw, "LocalDraw"},
    {GameWin, "GameWin"},
    {GameDraw, "GameDraw"},
    {Unknown, nullptr}
});

class TextManager{

    public:
    TextManager();
    
    void clearDictionary();
    
    bool replaceString(std::string& source, std::string_view replacement, std::string_view target);

    bool loadJSONCategoryToDictionary(const json& jsonFile, std::string_view sub);
    void loadJSONToDictionary(const json& jsonFile);

    std::string getText(TextOptions key);

    private:
    std::map<TextOptions, std::string> dict;

};