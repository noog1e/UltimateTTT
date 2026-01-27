#include "InputController.hpp"
#include "BoardLayout.hpp"
#include <iostream>
#include <cstddef>
#include <charconv>
#include <system_error>
#include <string>
#include <optional>

GameInputController::GameInputController(){}

bool GameInputController::integerInputError(const std::from_chars_result& result){
    return result.ec != std::errc{};
}

bool GameInputController::pointerPosError(const std::from_chars_result& result, std::string_view line){
    return result.ptr == line.data() + line.size();
}

bool GameInputController::integerBoundsError(int input){
    return input >= 0 && input < BoardLayout::NUM_CELLS;
}

std::optional<size_t> GameInputController::getInput(){

    std::string line;
    int input = 0;

    std::getline(std::cin, line);
        
    std::from_chars_result result = 
        std::from_chars(line.data(), line.data() + line.size(), input);
    
    if(integerInputError(result)) return std::nullopt;
    if(pointerPosError(result, line)) return std::nullopt;
    if(integerBoundsError(input)) return std::nullopt;

    return static_cast<size_t>(input);
}