#pragma once

#include <cstddef>
#include <string>
#include <charconv>
#include <optional>

class GameInputController{

    public:
    GameInputController();
    
    std::optional<size_t> readSizeInRange(size_t min, size_t max);
    std::optional<size_t> readSize();
    std::string readString();

    private:
    bool integerInputError(const std::from_chars_result& result);
    bool pointerPosError(const std::from_chars_result& result, std::string_view line);
    bool integerBoundsError(int input);
};

