#include "InputController.hpp"
#include "BoardLayout.hpp"
#include <iostream>
#include <cstddef>
#include <charconv>
#include <system_error>
#include <string>
#include <optional>

InputController::InputController(){}

bool InputController::integerInputError(const std::from_chars_result& result){
    return result.ec != std::errc{};
}

bool InputController::pointerPosError(const std::from_chars_result& result, std::string_view line){
    return result.ptr != line.data() + line.size();
}

bool InputController::integerBoundsError(int input){
    return input < 0 || input >= BoardLayout::NUM_CELLS;
}

std::optional<size_t> InputController::readSizeInRange(size_t min, size_t max){

    auto val = readSize();
    return (val && *val >= min && *val <= max) ? val : std::nullopt;
}

std::optional<size_t> InputController::readSize(){

    std::string line;
    int input = 0;

    if(std::getline(std::cin, line)) return std::nullopt;
        
    std::from_chars_result result = 
        std::from_chars(line.data(), line.data() + line.size(), input);
    
    if(integerInputError(result) || pointerPosError(result, line) || input < 0){
        return std::nullopt;
    } 

    return static_cast<size_t>(input);
}

std::string InputController::readString(){

    std::string line;

    std::getline(std::cin, line);

    return line;
}