#include "TextManager.hpp"
#include "LoadAssets.hpp"
#include "json.hpp"
#include <string>
#include <cstddef>
#include <map>

static const std::map<std::string, TextOptions> stringToEnum = {
    {"PlayGame",        TextOptions::PlayGame},
    {"HowToPlayBtn",    TextOptions::HowToPlayBtn},
    {"Exit",            TextOptions::Exit},
    {"HowToPlayTxt",    TextOptions::HowToPlayTxt},
    {"EntityTypes",     TextOptions::EntityTypes},
    {"PlayerNames",     TextOptions::PlayerNames},
    {"CoinFlip",        TextOptions::CoinFlip},
    {"FirstPlayer",     TextOptions::FirstPlayer},
    {"MarkerSelection", TextOptions::MarkerSelection},
    {"SetupConfirmed",  TextOptions::SetupConfirmed},
    {"CurrentPlayer",   TextOptions::CurrentPlayer},
    {"CurrentOuter",    TextOptions::CurrentOuter},
    {"CellSelected",    TextOptions::CellSelected},
    {"FreeMove",        TextOptions::FreeMove},
    {"InvalidMove",     TextOptions::InvalidMove},
    {"PositionNA",      TextOptions::PositionNA},
    {"LocalWin",        TextOptions::LocalWin},
    {"LocalDraw",       TextOptions::LocalDraw},
    {"GameWin",         TextOptions::GameWin},
    {"GameDraw",        TextOptions::GameDraw}
};

TextManager::TextManager(){}

std::string TextManager::replaceString(std::string source, const std::string& replacement, const std::string& target){

    size_t index = source.find(target);
    
    if(index != std::string::npos){
        source.replace(index, target.length(), replacement);
    }

    return source;
}

void TextManager::loadFileToString(const json& jsonFile, std::string_view sub){
    
    auto category = jsonFile[sub];
}

std::string TextManager::getText(TextOptions key){
    
}

TextOptions TextManager::bridgeStringToEnum(const std::string& key){
    auto it = stringToEnum.find(key);
    return (it != stringToEnum.end()) ? it->second : TextOptions::Unknown;
}