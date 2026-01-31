#include "Renderer.hpp"
#include <iostream>
#include <string>

Renderer::Renderer(){}

void Renderer::printLine(std::string_view line){
    std::cout << line << "\n";
}