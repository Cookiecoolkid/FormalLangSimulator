#pragma once

#include <string>
#include <set>
#include <map>
#include <tuple>
#include <vector>
#include "automata.h"
#include "pda_parser.h"

class PDA : public Automata {
public:
    PDA(const std::string& filename, PDAParser* parser);
    void printAutomata() const override;

private:
    std::set<std::string> states;
    std::set<char> inputSymbols;
    std::set<char> stackSymbols;
    std::string startState;
    char startStackSymbol;
    std::set<std::string> acceptStates;
    std::map<std::tuple<std::string, char, char>, std::tuple<std::string, std::string>> transitionFunctions;
    PDAParser* parser;
};