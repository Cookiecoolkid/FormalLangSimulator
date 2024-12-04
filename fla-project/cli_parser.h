#pragma once

#include "parser.h"
#include <string>
#include <vector>

class CLIParser : public Parser {
public:
    CLIParser(int argc, char* argv[]);
    ~CLIParser();
    void parse(const std::string& filename) override;

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