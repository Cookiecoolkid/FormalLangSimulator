#pragma once

#include "parser.h"
#include <string>
#include <set>
#include <map>
#include <tuple>
#include <vector>


class TMParser : public Parser {
public:
    void parse(const std::string& filename) override;

    std::set<std::string> states;
    std::set<char> inputSymbols;
    std::set<char> tapeSymbols;
    std::string startState;
    char blankSymbol;
    std::set<std::string> acceptStates;
    int numTapes;
    std::map<std::tuple<std::string, std::string>, std::tuple<std::string, std::string, std::string>> transitionFunctions;
};