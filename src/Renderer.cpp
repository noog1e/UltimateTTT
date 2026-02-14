#include "Renderer.hpp"
#include <iostream>
#include <string>

Renderer::Renderer(){}

void Renderer::printLine(std::string_view line){
    std::cout << line << "\n";
}

void Renderer::printLine(std::string_view line, bool newLine){
    
    std::cout << line;

    if(newLine){
        std::cout << "\n";
    }
}