#pragma once

#include "LoadAssets.hpp"
#include "json.hpp"
#include <map>
#include <string>
#include <filesystem>

using json = nlohmann::json;

static constexpr char JSON_NAME[] = "{NAME}";

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

class TextManager{

    public:
    TextManager();
    
    std::string replaceString(std::string source, const std::string& replacement, const std::string& target);

    void loadFileToString(const json& jsonFile, std::string_view sub);

    std::string getText(TextOptions key);

    private:
    std::map<TextOptions, std::string> dict;

    TextOptions bridgeStringToEnum(const std::string& key);

};