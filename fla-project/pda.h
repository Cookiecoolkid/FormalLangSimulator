#pragma once

#include <string>
#include <set>
#include <map>
#include <tuple>
#include <stack>
#include <vector>
#include "automata.h"
#include "pda_parser.h"

class PDA : public Automata {
public:
    PDA(const std::string& filename, PDAParser* parser);
    void simulate(const std::string& input, bool verbose) override;
    void printAutomata() const override;

    void stepInfo_verbose(int step, const std::string& currentState, const char& inputSymbol) const;
private:
    std::set<char> stackSymbols;
    char startStackSymbol;
    std::set<std::string> acceptStates;
    std::map<std::tuple<std::string, char, char>, std::tuple<std::string, std::string>> transitionFunctions;
    PDAParser* parser;
    std::stack<char> stack;
};