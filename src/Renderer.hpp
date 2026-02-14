#pragma once

#include <iostream>
#include <string>

class Renderer{

    public:
    Renderer();
    void printLine(std::string_view line);
    void printLine(std::string_view line, bool newLine);

    private:
    //TODO colours, and other stuff
};