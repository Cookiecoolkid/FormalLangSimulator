#pragma once

#include "parser.h"
#include <string>
#include <vector>

class CLIParser {
public:
    CLIParser(int argc, char* argv[]);
    ~CLIParser();

    enum class AutomataType {
        PDA,
        TM,
        EMPTY
    };

    AutomataType automataType = AutomataType::EMPTY;
    std::string model;
    std::string input;
    bool verbose;

private:
    void parseArguments(int argc, char* argv[]);
};