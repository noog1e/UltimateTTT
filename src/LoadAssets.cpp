#include "LoadAssets.hpp"
#include "json.hpp"
#include <string>
#include <filesystem>
#include <fstream>
#include <optional>

LoadAssets::LoadAssets(){}

std::optional<json> LoadAssets::loadJSON(const std::filesystem::path& filepath){

    std::ifstream ifs(filepath);

    if(ifs && json::accept(ifs)){
        return json::parse(ifs);
    } 

    return std::nullopt;
}