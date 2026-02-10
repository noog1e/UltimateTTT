#include "AssetLoader.hpp"
#include "json.hpp"
#include <string>
#include <filesystem>
#include <fstream>
#include <optional>

AssetLoader::AssetLoader(){}

std::optional<json> AssetLoader::loadJSON(const std::filesystem::path& filepath){

    std::ifstream ifs(filepath);

    if(!ifs) return std::nullopt;
    
    json j = json();

    try{
        j = json::parse(ifs);
    }catch(const json::parse_error& e){
        return std::nullopt;
    }

    return j;
}