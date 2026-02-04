#pragma once

#include "json.hpp"
#include <string>
#include <filesystem>
#include <optional>

using json = nlohmann::json;

class LoadAssets{

    public:
    LoadAssets();

    std::optional<json> loadJSON(const std::filesystem::path& filepath);

    private:
};