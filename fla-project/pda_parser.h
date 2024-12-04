#pragma once

#include <string>
#include "parser.h"
#include <set>
#include <map>
#include <tuple>

class PDAParser : public Parser {
public:
    void parse(const std::string& filename) override;
    std::set<std::string> states;
    std::set<char> inputSymbols;
    std::set<char> stackSymbols;
    std::string startState;
    char startStackSymbol;
    std::set<std::string> acceptStates;
    std::map<std::tuple<std::string, char, char>, std::tuple<std::string, std::string>> transitionFunctions;
};