#include "AssetLoader.hpp"
#include "json.hpp"
#include <string>
#include <filesystem>
#include <fstream>
#include <optional>

AssetLoader::AssetLoader(){}

std::optional<json> AssetLoader::loadJSON(const std::filesystem::path& filepath){

    std::ifstream ifs(filepath);

    if(ifs && json::accept(ifs)){
        return json::parse(ifs);
    } 

    return std::nullopt;
}