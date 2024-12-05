#pragma once

#include <string>
#include <set>
#include <map>
#include <tuple>
#include <vector>
#include <deque>
#include "automata.h"
#include "tm_parser.h"

class TM : public Automata {
public:
    TM(const std::string& filename, TMParser* parser);
    void simulate(const std::string& input, bool verbose) const override;
    void checkInput(const std::string& input) const override;
    void printAutomata() const override;
    void printTapes() const;

private:
    std::set<std::string> states;
    std::set<char> inputSymbols;
    std::set<char> tapeSymbols;
    std::string startState;
    char blankSymbol;
    std::set<std::string> acceptStates;
    int numTapes;
    std::map<std::tuple<std::string, std::string>, std::tuple<std::string, std::string, std::string>> transitionFunctions;
    TMParser* parser;

    std::vector<std::deque<char>> tapes;
    std::vector<int> heads;
};