#include "TextManager.hpp"
#include "LoadAssets.hpp"
#include "json.hpp"
#include <string>
#include <cstddef>
#include <map>
#include <optional>

using json = nlohmann::json;

TextManager::TextManager(){}

void TextManager::clearDictionary(){
    dict.clear();
}

bool TextManager::replaceString(std::string& source, const std::string& replacement, const std::string& target){

    size_t index = source.find(target);
    
    if(index != std::string::npos){
        source.replace(index, target.length(), replacement);
        return true;
    }

    return false;
}

bool TextManager::loadJSONCategoryToDictionary(const json& jsonFile, std::string_view sub){

    if(!jsonFile.contains(sub)) return false;
        
    for(auto& [key, value] : jsonFile[sub].items()){
        TextOptions enumKey = json(key).get<TextOptions>();
        dict[enumKey] = value;
    }

    return true;
}

void TextManager::loadJSONToDictionary(const json& jsonFile){

    for(auto& [key, value] : jsonFile.items()){
        TextOptions enumKey = json(key).get<TextOptions>();
        dict[enumKey] = value;
    }
}

std::string TextManager::getText(TextOptions key){
    return dict.at(key);
}