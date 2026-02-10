#include "TextManager.hpp"
#include "LoadAssets.hpp"
#include "json.hpp"
#include <string>
#include <cstddef>
#include <map>
#include <optional>
#include <iostream>

using json = nlohmann::json;

TextManager::TextManager(){}

void TextManager::clearDictionary(){
    dict.clear();
}

void TextManager::replaceString(std::string& source, std::string_view replacement, std::string_view target){

    size_t index = source.find(target);
    
    if(index != std::string::npos){
        source.replace(index, target.length(), replacement);
    } else{
        std::cerr << "Invalid Placeholder: " << target << "\n";
    }

}

bool TextManager::loadJSONCategoryToDictionary(const json& jsonFile, std::string_view sub){

    auto it = jsonFile.find(sub);

    if(it == jsonFile.end()) return false;
        
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
    
    auto it = dict.find(key);

    if(it == dict.end()){
        std::cerr << "Key not found in dictionary. Enum ID: " << static_cast<int>(key) << "\n";
        return "!!!MISSING!!!";
    }

    return dict.at(key);
}

std::string TextManager::getText(TextOptions key, std::string_view replacement, std::string_view target){
    
    auto it = dict.find(key);
    
    if(it == dict.end()){
        std::cerr << "Key not found in dictionary. Enum ID: " << static_cast<int>(key) << "\n";
        return "!!!MISSING!!!";
    }

    std::string source = it->second;
    replaceString(source, replacement, target);

    return source;
}